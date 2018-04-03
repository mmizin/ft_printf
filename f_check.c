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

//void	f_chk(va_list ap, const char *format, int *bp)
void	f_chk(va_list ap, const char *format, t_var *v)
{
	while (format && *format)
	{
		if (f_no_perc_at_all(&format, v))
			return ;
		f_chk_let_conv(&format, ap, v);
	}

}
