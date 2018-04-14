//
// Created by mizman on 04.04.18.
//

#include "ft_printf.h"

static int	f_find_weight(const char **format, char c, va_list ap);
static int	f_find_bytes(t_var *v, wchar_t res);
static void f_C_ls_print(t_var *v, wchar_t res);

int     f_perc_C_big(va_list ap, const char **format, t_var *v)
{
    wchar_t res;

    v->ts == l ? (v->res = 'c') : (v->res  = 'C');
    v->w = f_find_weight(format, v->res, ap);
    res = va_arg(ap, wint_t);
	f_find_bytes(v, res);
	if ((v->i = MB_CUR_MAX) != 4 && v->cur_max == 1)
	{
		v->bp = -1;
		(**format != '\0') && (*format)++;
		return (0);
	}
	if (v->w > v->l)
		(v->bp += f_w_e_l(' ', v->w - v->l));
	else if (v->w < 0)
			v->sign = (v->w * -1) > v->l ? (v->w * -1) - v->l : 0;
	f_C_ls_print(v, res);
	while (**format != v->res)
		(*format)++;
	(**format != '\0') && (*format)++;
	f_reset_init(v);
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

static int f_find_bytes(t_var *v, wchar_t res)
{
	v->l = 0;
	v->i = res;
	if (v->i <= 127)
		v->l = 1;
	else if (v->i <= 2027)
		(v->l = 2) && (v->cur_max = 1);
	else if (v->i <= 65535)
		(v->l = 3) && (v->cur_max = 1);
	else
		(v->l = 4) && (v->cur_max = 1);
	return (1);
}

static void f_C_ls_print(t_var *v, wchar_t res)
{
		v->i = res;
		if (v->i <= 127)
			(v->bp += write(1, &res, 1)) && (v->p -= 1);
		else if (v->i <= 2047)
		{
			(res = v->i >> 6 | 0xc0) && (v->bp += write(1, &res, 1));
			(res = (v->i & 0x003F) | 0x80) && (v->bp += write(1, &res, 1)) && (v->p -= 2);
		}
		else if (v->i <= 65535)
		{
			(res = v->i >> 12 | 0xE0) && (v->bp += write(1, &res, 1));
			(res = (v->i >> 6 & 0x3F) | 0x80) && (v->bp += write(1, &res, 1));
			(res = (v->i & 0x3F) | 0x80) && (v->bp += write(1, &res, 1)) && (v->p -= 3);
		}
		else if (v->l >= 4)
		{
			(res = v->i >> 18 | 0xF0) && (v->bp += write(1, &res,1));
			(res = ((v->i >> 12) & 0x3F) | 0x80) && (v->bp += write(1, &res, 1));
			(res = ((v->i >> 6) & 0x3F) | 0x80) && (v->bp += write(1, &res, 1));
			(res = (v->i & 0x3F) | 0x80) && (v->bp += write(1, &res, 1)) && (v->p -= 4);
		}
	(v->sign) && (v->bp += f_w_e_l(' ', v->sign)) && (v->sign = 0);
}
