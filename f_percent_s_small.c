/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_percent_s_small.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 06:24:33 by nmizin            #+#    #+#             */
/*   Updated: 2018/02/22 06:24:36 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		f_find_weight(const char **format, char c, va_list ap);
static	int		f_find_precision(const char **format, char c, va_list ap);
static	int		f_if_handler(t_var *v, va_list ap);

int		f_perc_s_small(va_list ap, const char **format, t_var *v)
{
	va_list	first;
	va_list second;

	v->w = f_find_weight(format, v->res, ap);
	v->p = f_find_precision(format, v->res, ap);
	va_copy(first, ap);
	v->l = ft_strlen(va_arg(first, char *));
	va_copy(second, ap);
	if (!va_arg(second, char *))
	{
		(**format != '\0' && **format == v->res) && (*format)++;
		return (write(1, "(null)", 6) && (v->bp += 6) && va_arg(ap, char *));
	}
	f_if_handler(v, ap);
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
			while (**format >= '0' && **format <= '9')
				(*format)++;
			return (width);
		}
		(**format != c && **format != '.') && (*format)++;
	}
	return (0);
}

static	int		f_find_precision(const char **format, char c, va_list ap)
{
	int		prec;
	int		point;
	va_list	first;

	prec = 0;
	point = 0;
	va_copy(first, ap);
	while (**format && **format != c)
	{
		if (**format == '.')
		{
			point++;
			if (*(*format + 1) == '*')
				prec = va_arg(ap, int);
			if ((*(*format + 1) >= '0' && *(*format + 1) <= '9'))
				prec = ft_atoi((*format) + 1);
		}
		(**format != c) && (*format)++;
	}
	if (!point)
		return (point = ft_strlen(va_arg(first, char *)));
	return (prec);
}

static	int		f_if_handler(t_var *v, va_list ap)
{
	int tmp;

	if (v->p == 0 || v->p <= v->l)
		v->l = v->p;
	if (v->w >=0 && v->w <= v->l)
		v->w = v->l;
	if (v->w < 0)
		tmp = (v->w * -1) > v->l ? (v->w * -1) - v->l : 0;
	if (v->w >= 0 && v->w >= v->l)
	{
		v->bp += f_w_e_l(' ', v->w - v->l);
		v->bp += write(1, va_arg(ap, char *), v->l);
	}
	else if (v->w < 0)
	{
		v->bp += write(1, va_arg(ap, char *), v->l);
		v->bp += f_w_e_l(' ', tmp);
	}
//	if (v->w > v->l && v->p >= v->l)
//		(v->bp += f_w_e_l(' ', v->w - v->l))
//		&& (v->bp += write(1, va_arg(ap, char *), v->l));
//	else if (v->w >= 0 && v->p > v->l && v->w <= v->l)
//		v->bp += write(1, va_arg(ap, char *), v->l);
//	else if (v->w >= 0 && v->p < v->l && v->w >= v->l)
//		(v->bp += f_w_e_l(' ', v->w - v->p))
//		&& (v->bp += write(1, va_arg(ap, char *), v->p));
//	else if (v->w < 0 && v->p <= v->l && (v->w * -1) >= v->p)
//		(v->bp += write(1, va_arg(ap, char *), v->p))
//		&& (v->bp += f_w_e_l(' ', (v->w * -1) - v->p));
//	else if (v->w < 0 && v->p > v->l && (v->w * -1) >= v->p)
//		(v->bp += write(1, va_arg(ap, char *), v->l))
//		&& (v->bp += f_w_e_l(' ', (v->w * -1) - v->l));
//	else if (v->w < 0 && v->p <= v->l && (v->w * -1) < v->p)
//		v->bp += write(1, va_arg(ap, char *), v->p);
//	else if (v->w < 0 && v->p > v->l && (v->w * -1) < v->p)
//		v->bp += write(1, va_arg(ap, char *), v->l);
//	else if ((v->w >= 0 && v->p <= v->l && v->w <= v->l) || (v->w == 0 && v->p == 0))
//		v->bp += write(1, va_arg(ap, char *), v->p);
	return (1);
}