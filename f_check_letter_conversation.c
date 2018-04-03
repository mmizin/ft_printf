/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check_letter_conversation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 05:53:40 by nmizin            #+#    #+#             */
/*   Updated: 2018/02/22 05:59:58 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	f_fin_letr(const char *format, t_var v);
static	char	f_size_sp(char **res, t_var v);

void		f_chk_let_conv(const char **format, va_list ap, t_var *v)
{
	v->res = f_fin_letr(*format, *v);
	if (v->res == 's')
		f_perc_s_small(ap, format, v);
	else if (v->res == 'p')
		(*format)++;
	else if (v->res == 'd')
		(*format)++;
	else if (v->res == 'D')
		(*format)++;
	else if (v->res == 'i')
		(*format)++;
	else if (v->res == 'o')
		(*format)++;
	else if (v->res == 'O')
		(*format)++;
	else if (v->res == 'u')
		(*format)++;
	else if (v->res == 'U')
		(*format)++;
	else if (v->res == 'x')
		(*format)++;
	else if (v->res == 'X')
		(*format)++;
	else if (v->res == 'c')
		(*format)++;
	else if (v->res == 'C')
		(*format)++;
	else if (v->res == 'S')
		f_perc_S_big(ap, format, v);
	else
		(*format)++;
}

static	char	f_fin_letr(const char *format, t_var v)
{
	v.begin = format;
	char *res;
	char res_sp;
	while (format && *format)
	{
		if ((res = (ft_strchr(CONVERSIONS, *format))) != NULL)
			break;
		format++;
	}
	if (res == NULL)
		return (0);
	while ((v.begin && *(v.begin)) && *(v.begin) != *res)
	{
		(*(v.begin) == 'l' && *(v.begin + 1) != 'l') && (v.ts = l);
		(*(v.begin) == 'l' && *(v.begin + 1) == 'l') && (v.ts = ll);
		(*(v.begin) == 'h' && *(v.begin + 1) != 'h') && (v.ts = h);
		(*(v.begin) == 'h' && *(v.begin + 1) == 'h') && (v.ts= hh);
		(*(v.begin) == 'j') && (v.ts = j);
		(*(v.begin) == 'z')	&& (v.ts = z);
		v.begin++;
	}
	return ((res_sp = f_size_sp(&res, v)) ? res_sp : *res);
}

static	char	f_size_sp(char **res, t_var v)
{
	if (v.ts == l && **res == 's')
		return ('S');
	else
		return (0);

}
