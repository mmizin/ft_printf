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

static int f_check_any_letter_init(va_list ap, const char **format, t_var *v);

void	f_chk(va_list ap, const char *format, t_var *v)
{
    const char  *tmp;
    int         f_res;

    tmp = format;
	while (format && *format)
	{
		if (f_no_perc_at_all(&format, v))
			return ;
		if (!(f_res = f_check_any_letter_init(ap, &format, v)))
			return ;
        if (f_res == 1)
		    f_chk_let_conv(&format, ap, v);
        else if (f_res == 2)
        {
            format = tmp;
            f_chk_let_conv(&format, ap, v);
        }
	}

}

static int f_check_any_letter_init(va_list ap, const char **format, t_var *v)
{
	char *tmp;

    (*format)++ && (v->begin = *format);
	while (*format && **format)
	{
		if ((tmp = (ft_strchr(CONVERSIONS, **format))) != NULL || **format == '%')
			break;
		(*format)++;
	}
	if (tmp == NULL)
	{
       if (!f_from_per_to_per(ap, format, v))
           return (0);
        else
           return (1);
	}
	return (2);
}