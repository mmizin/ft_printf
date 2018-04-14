/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 06:15:31 by nmizin            #+#    #+#             */
/*   Updated: 2018/02/22 06:19:39 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	f_check_any_letter_init(va_list ap, const char **format, t_var *v)
{
	char *tmp;

	v->begin = (*format + 1);
	while (*(v->begin))
	{
		if ((tmp = (ft_strchr(CONVERSIONS, *(v->begin)))) != NULL
			|| *(v->begin) == '%')
			break ;
		v->begin++;
	}
	if (tmp == NULL)
		f_from_per_to_per(ap, format, v);
	return (1);
}

void		f_chk(va_list ap, const char *format, t_var *v)
{
	while (format && *format)
	{
		f_reset_init(v);
		if (f_no_perc_at_all(&format, v))
			return ;
		f_check_any_letter_init(ap, &format, v);
		if (f_no_perc_at_all(&format, v))
			return ;
		f_chk_let_conv(&format, ap, v);
	}
}
