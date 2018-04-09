//
// Created by Nikolay MIZIN on 3/2/18.
//
#include "ft_printf.h"

static int	f_find_weight(const char **format, char c, va_list ap);
static void f_find_precision(const char **format, char c, va_list ap, t_var *v);
static int	f_find_bytes(t_var *v, wchar_t *str);
static void f_S_ls_print(t_var *v, wchar_t *str, wchar_t res);

int f_perc_S_big(va_list ap, const char **format, t_var *v)
{
	wchar_t *str;
	wchar_t res;

	res = '\0';
	v->ts == l ? (v->res = 's') : (v->res  = 'S');
	v->w = f_find_weight(format, v->res, ap);
	f_find_precision(format, v->res, ap, v);
	if (!(str = va_arg(ap, wchar_t *)))
	{
		(**format != '\0' && (**format == v->res || **format == v->res)) && (*format)++;
		return (write(1, "(null)", 6) && (v->bp += 6));
	}
	f_find_bytes(v, str);
	if (MB_CUR_MAX != 4 && v->cur_max == 1)
	{
		v->bp = -1;
		(**format != '\0') && (*format)++;
		return (0);
	}
	if (v->w > v->l)
		(v->bp += f_w_e_l(' ', v->w - v->l));
	else if (v->w < 0)
			v->sign = (v->w * -1) > 0 ? (v->w * -1) - v->l : 0;
	f_S_ls_print(v, str, res);
	(**format != '\0') && (*format)++;
	return (1);
}

static	int		f_find_weight(const char **format, char c, va_list ap)
{
	int		width;
	int		sign;

	sign = 1;
	while (format && **format != c && **format != '.')
	{
		if (**format == '-')
			sign = -1;
		if (**format == '*')
		{
			width = va_arg(ap, int);
			width = width < 0 ? width : width * sign;
			return (width);
		}
		if (**format >= '1' && **format <= '9')
		{
			width = ft_atoi(*format) * sign;
			while ((**format >= '0' && **format <= '9') || **format == 'l')
				(*format)++;
			return (width);
		}
		(**format != c && **format != '.') && (*format)++;
	}
	return (0);
}

static void f_find_precision(const char **format, char c, va_list ap, t_var *v)
{
	int		point;
	va_list	first;

	point = 0;
	v->p = 0;
	va_copy(first, ap);
	while (**format && **format != c)
	{
		if (**format == '.')
		{
			point++;
			if (*(*format + 1) == '*')
				v->p = va_arg(ap, int);
			if ((*(*format + 1) >= '0' && *(*format + 1) <= '9'))
				v->p = ft_atoi((*format) + 1);
		}
		(**format != c) && (*format)++;
	}
	if (!point)
		v->p = -1;
}

static int f_find_bytes(t_var *v, wchar_t *str)
{
	v->l = 0;
		while (*str)
		{
			v->i = *str++;
			if (v->i <= 127)
				v->l += 1;
			else if (v->i <= 2027)
				(v->l += 2) && (v->cur_max = 1);
			else if (v->i <= 65535)
				(v->l += 3) && (v->cur_max = 1);
			else
				(v->l += 4) && (v->cur_max = 1);
			if (v->p >= v->l)
				(v->p -= v->l);
			if (v->l >= v->p && v->p > 0)
			{
				v->p = v->l;
				break ;
			}
	}
	if (v->p < 0)
		v->p = v->l;
	return (1);
}

static void f_S_ls_print(t_var *v, wchar_t *str, wchar_t res)
{
	while(*str)
	{
		v->i = *str++;
		if (v->i <= 127 && v->p >= 1)
			(v->bp += write(1, str-1, 1)) && (v->p -= 1);
		else if (v->i <= 2047 && v->p >= 2)
		{
			(res = v->i >> 6 | 0xc0) && (v->bp += write(1, &res, 1));
			(res = (v->i & 0x003F) | 0x80) && (v->bp += write(1, &res, 1)) && (v->p -= 2);
		}
		else if (v->i <= 65535 && v->p >= 3)
		{
			(res = v->i >> 12 | 0xE0) && (v->bp += write(1, &res, 1));
			(res = (v->i >> 6 & 0x3F) | 0x80) && (v->bp += write(1, &res, 1));
			(res = (v->i & 0x3F) | 0x80) && (v->bp += write(1, &res, 1)) && (v->p -= 3);
		}
		else if (v->p >= 4)
		{
			(res = v->i >> 18 | 0xF0) && (v->bp += write(1, &res,1));
			(res = ((v->i >> 12) & 0x3F) | 0x80) && (v->bp += write(1, &res, 1));
			(res = ((v->i >> 6) & 0x3F) | 0x80) && (v->bp += write(1, &res, 1));
			(res = (v->i & 0x3F) | 0x80) && (v->bp += write(1, &res, 1)) && (v->p -= 4);
		}
	}
	(v->sign) && (v->bp += f_w_e_l(' ', v->sign)) && (v->sign = 0);
}