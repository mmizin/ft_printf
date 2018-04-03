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

#include <tclDecls.h>
#include "ft_printf.h"

static int f_check_any_letter_init(va_list ap, const char *format, t_var *v);
void	f_chk(va_list ap, const char *format, t_var *v)
{
	while (format && *format)
	{
		if (f_no_perc_at_all(&format, v))
			return ;
		if (f_check_any_letter_init(ap, &format, v))
			return ;
		f_chk_let_conv(&format, ap, v);
	}

}

static int f_check_any_letter_init(va_list ap, const char *format, t_var *v)
{
	v->begin = format;
	
}