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
	const char	*begin;

	begin = *format;
	while (**format)
	{
		if (**format == '%' && *(*format + 1) == '%')
		{
			(v->c) && write(1, begin, v->c);
			write(1, "%", 1) && v->bp++;
			(*format) += 2;
			v->c = 0;
			begin = *format;
		}
		if (**format == '%' && *(*format + 1) != '%')
		{
			(v->c) && write(1, begin, v->c);
			(v->bp += v->c) && (v->c = 0);
			return (0);
		}
		(**format != '\0' ) && (*format)++ && v->c++;
	}
	write(1, begin, v->c);
	v->bp += v->c;
	return (1);
}
