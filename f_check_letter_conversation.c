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

static	char	f_fin_letr(const char *format, t_var *v);
static	char	f_size_sp(char **res, t_var *v);
static	int		f_init_enum(const char *format, t_var *v, char *res);

void		f_chk_let_conv(const char **format, va_list ap, t_var *v)
{
	v->res = f_fin_letr(*format, v);
	if (v->res == 's' && f_perc_s_small(ap, format, v))
        ;
	else if (v->res == 'p')
		(*format)++;
	else if (v->res == 'd' && f_perc_d_small(ap, format, v))
        ;
	else if (v->res == 'D')
		(*format)++;
	else if (v->res == 'i' && f_perc_d_small(ap, format, v))
		;
	else if (v->res == 'o')
		(*format)++;
	else if (v->res == 'O')
		(*format)++;
	else if (v->res == 'u')
		(*format)++;
	else if (v->res == 'U')
		(*format)++;
	else if (v->res == 'x' && f_perc_x_X(ap, format, v))
        ;
	else if (v->res == 'X')
		(*format)++;
	else if (v->res == 'c' && f_perc_c_small(ap, format, v))
		;
	else if (v->res == 'C' && f_perc_C_big(ap, format, v))
		;
	else if (v->res == 'S' && f_perc_S_big(ap, format, v))
		;
	else if (**format)
        (*format)++;
}

static	char	f_fin_letr(const char *format, t_var *v)
{
	v->begin = format;
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
	f_init_enum(format, v, res);
	return ((res_sp = f_size_sp(&res, v)) ? res_sp : *res);
}

static	char	f_size_sp(char **res, t_var *v)
{
	if (v->ts == l && **res == 's')
		return ('S');
	else if (v->ts == l && **res == 'c')
	    return ('C');
	else
		return (0);
}

static	int		f_init_enum(const char *format, t_var *v, char *res)
{
	while ((format && *(v->begin)) && *(v->begin) != *res)
	{
		if ((*(v->begin) == 'l' && *(v->begin + 1) != 'l') && (v->ts = l))
			break ;
		else if (*(v->begin) == 'l' && *(v->begin + 1) == 'l')
		{
			v->ts = ll;
			break ;
		}
		else if (*(v->begin) == 'h' && *(v->begin + 1) == 'h')
		{
			v->ts = hh;
			break ;
		}
		else if ((*(v->begin) == 'h' && (v->ts = h)))
			break ;
		else if ((*(v->begin) == 'j') && (v->ts = j))
			break ;
		else if ((*(v->begin) == 'z') && (v->ts = z))
			break ;
		v->begin++;
	}
	return (1);
}
