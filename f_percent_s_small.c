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
static	int		f_if_handler(t_var *v, char *argv);

int		f_perc_s_small(va_list ap, const char **format, t_var *v)
{
    char    *argv;

	v->w = f_find_weight(format, v->res, ap);
	v->p = f_find_precision(format, v->res, ap);
    argv = va_arg(ap, char *);
	v->l = ft_strlen(argv);
	f_if_handler(v, argv);
    f_reset_init(v);
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
		return (-1);
	return (prec);
}

static	int		f_if_handler(t_var *v, char *argv)
{
	int tmp;

	(!argv) && (v->l = 6);
	if (v->p == 0 || (v->p >= 0 && v->p <= v->l))
		v->l = v->p;
	if (v->w >=0 && v->w <= v->l)
		v->w = v->l;
	if (v->w < 0)
		tmp = (v->w * -1) > v->l ? (v->w * -1) - v->l : 0;
	if (v->w >= 0 && v->w >= v->l)
	{
		v->bp += f_w_e_l(' ', v->w - v->l);
        if (!argv)
            v->bp += write(1, "(null)", v->l);
		else
			v->bp += write(1, argv, v->l);
	}
	else if (v->w < 0)
	{
		if (!argv)
			v->bp += write(1, "(null)", v->l);
		else
			v->bp += write(1, argv, v->l);
		v->bp += f_w_e_l(' ', tmp);
	}
	return (1);
}
