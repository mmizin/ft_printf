/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_from_perc_to_perc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:33:57 by nmizin            #+#    #+#             */
/*   Updated: 2018/04/14 17:01:10 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		f_find_weight(const char **format, char c, va_list ap)
{
	int			width;
	int			sign;

	sign = 1;
	(**format == '%') && (*format)++;
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

static int		f_find_precision(const char **format, char c, va_list ap)
{
	int		prec;
	int		point;

	prec = 0;
	point = 0;
	while (**format && **format != c)
	{
		if ((**format == '.') && ++point)
		{
			if (*(*format + 1) == '*')
				prec = va_arg(ap, int);
			if ((*(*format + 1) >= '0' && *(*format + 1) <= '9') && (*format)++)
			{
				prec = ft_atoi(*format);
				while (**format && (**format >= '0' && **format <= '9'))
					(*format)++;
				return (0);
			}
		}
		(**format != c) && (*format)++;
	}
	return (0);
}

static int		f_if_handler(t_var *v)
{
	if (v->zer && v->w == 0)
		v->zer = 0;
	if (v->min)
		v->zer = 0;
	if (v->w >= 0)
	{
		if (v->zer)
			v->bp += f_w_e_l('0', v->w - 1);
		else
			v->bp += f_w_e_l(' ', v->w - 1);
		v->bp += write(1, "%", 1);
	}
	else if (v->w < 0)
	{
		v->bp += write(1, "%", 1);
		if (v->zer)
			v->bp += f_w_e_l('0', (v->w * -1) - 1);
		else
			v->bp += f_w_e_l(' ', (v->w * -1) - 1);
	}
	return (1);
}

int				f_from_per_to_per(va_list ap, const char **format, t_var *v)
{
	f_sign(format, v);
	v->w = f_find_weight(format, '%', ap);
	v->p = f_find_precision(format, '%', ap);
	f_if_handler(v);
	(**format != '\0') && (*format)++;
	return (1);
}
