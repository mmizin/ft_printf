/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_no_perc_at_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 18:10:40 by nmizin            #+#    #+#             */
/*   Updated: 2018/02/27 18:10:42 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		f_no_perc_at_all(const char **format, t_var *v)
{
	v->begin = *format;
	v->c = 0;
	while (**format)
	{
		if (**format == '%' && *(*format + 1) == '%')
		{
			(v->c) && write(1, v->begin, v->c);
			write(1, "%", 1) && v->bp++;
			(*format) += 2;
			v->c = 0;
			v->begin = *format;
		}
		if (**format == '%' && *(*format + 1) != '%')
		{
			(v->c) && write(1, v->begin, v->c);
			(v->bp += v->c) && (v->c = 0);
			return (0);
		}
		(**format != '\0' ) && (*format)++ && v->c++;
	}
	v->bp += write(1, v->begin, v->c);
	return (1);
}
