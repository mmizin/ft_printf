/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 20:28:09 by nmizin            #+#    #+#             */
/*   Updated: 2018/02/25 20:29:37 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void f_initialize_struct(t_var *v)
{
	v->bp = 0;
	v->p = -1;
	v->w = 0;
	v->l = 0;
	v->c = 0;
	v->cur_max = 0;
	v->i = 0;
	v->sign = 0;
	v->begin = NULL;
	v->pl = 0;
	v->min = 0;
	v->hes = 0;
	v->spa = 0;
	v->zer = 0;
	v->tmp = 0;
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	t_var	v;

	va_start(ap, format);
	f_initialize_struct(&v);
	f_chk(ap, format, &v);
	va_end(ap);
	printf("\nmy_return = %d\n", v.bp);
	return (v.bp);
}
