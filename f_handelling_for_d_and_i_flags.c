/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_handelling_for_d_and_i_flags.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:03:36 by nmizin            #+#    #+#             */
/*   Updated: 2018/04/14 17:03:38 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		f_handl_prec_null(t_var *v, long long int v_arg)
{
	if (!v->p && !v_arg)
	{
		if (!v->pl)
		{
			if (v->w < 0 && (v->w = -v->w))
				;
			v->bp += f_w_e_l(' ', v->w = ((v->spa) && v->w == 0) ? 1 : v->w);
		}
		if (v->pl)
		{
			if (v->w >= 0)
				(v->bp += f_w_e_l(' ', --v->w)) && (v->bp += write(1, "+", 1));
			else if (v->w < 0)
			{
				v->w = v->w * -1 > 1 ? v->w * -1 - 1 : 1;
				v->bp += write(1, "+", 1) + f_w_e_l(' ', v->w);
			}
		}
		return (1);
	}
	return (0);
}

static int		f_part_one(t_var *v, char *argv)
{
	if (v->p == -1)
	{
		if (v->w >= 0)
		{
			v->w = v->w > v->l ? v->w - v->l - v->spa - v->pl - v->min : 0;
			if (v->zer)
				v->bp += write(1, " ", v->spa) + write(1, "+", v->pl)
				+ write(1, "-", v->min)
				+ f_w_e_l('0', v->w) + write(1, argv, v->l);
			if (!v->zer)
				v->bp += write(1, " ", v->spa) + f_w_e_l(' ', v->w)
			+ write(1, "+", v->pl)
			+ write(1, "-", v->min) + write(1, argv, v->l);
		}
		else if (v->w < 0)
		{
			v->w = (v->w * -1) > v->l ?
			(v->w * -1) - v->spa - v->l - v->pl - v->min : 0;
			v->bp += write(1, " ", v->spa)
			+ write(1, "+", v->pl) + write(1, "-", v->min)
			+ write(1, argv, v->l) + f_w_e_l(' ', v->w);
		}
	}
	return (v->p == -1 ? 1 : 0);
}

static int		f_part_two(t_var *v, char *argv)
{
	if (v->p >= 0)
	{
		v->p = v->p > v->l ? v->p - v->l : 0;
		if (v->w >= 0)
		{
			v->w = v->w > v->l ?
			v->w - v->l - v->spa - v->min - v->pl - v->p : 0;
			v->bp += write(1, " ", v->spa) + f_w_e_l(' ', v->w)
			+ write(1, "+", v->pl) + write(1, "-", v->min)
			+ f_w_e_l('0', v->p) + write(1, argv, v->l);
		}
		else if (v->w < 0)
		{
			v->w = (v->w * -1) > v->l
			? (v->w * -1) - v->l - v->spa - v->pl - v->min - v->p : 0;
			v->bp += write(1, " ", v->spa) + write(1, "+", v->pl)
			+ write(1, "-", v->min) + f_w_e_l('0', v->p)
			+ write(1, argv, v->l) + f_w_e_l(' ', v->w);
		}
	}
	return (1);
}

void			f_for_d_and_i_flags(t_var *v, long long int v_arg, char *argv)
{
	if (v->pl)
		v->spa = 0;
	if (v_arg < 0)
	{
		v->pl = 0;
		v->spa = 0;
		v->min = 1;
	}
	if (v_arg >= 0)
		v->min = v->min > 0 ? 0 : v->min;
	if (f_handl_prec_null(v, v_arg))
		return ;
	if (f_part_one(v, argv))
		return ;
	f_part_two(v, argv);
}
