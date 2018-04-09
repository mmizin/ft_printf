

#include "ft_printf.h"

static int	f_handl_prec_NULL(t_var *v, long long int v_arg);
static int	f_part_one(t_var *v, long long int v_arg, char *argv);
static int	f_part_two(t_var *v, long long int v_arg, char *argv);

void		f_for_d_and_i_flags(t_var *v, long long int v_arg, char *argv)
{
	if (f_handl_prec_NULL(v, v_arg))
        return ;
    if (f_part_one(v, v_arg, argv))
    	return ;

}

static int 		f_handl_prec_NULL(t_var *v, long long int v_arg)
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
				(v->bp += f_w_e_l(' ',--v->w)) && (v->bp += write(1, "+", 1));
			else if (v->w < 0)
			{
				v->w * -1 > 1 ? (v->w = v->w * -1 - 1) : (v->w = 1);
				(v->bp += write(1, "+", 1)) && (v->bp += f_w_e_l(' ', v->w));
			}
		}
		return (1);
	}
	return (0);
}

static int 		f_part_one(t_var *v, long long int v_arg, char *argv)
{
	v->tmp = v->w;
	if (v_arg < 0)
	{
		(v->min = 1) && (v->spa = 0);
		v->pl = 0;
	}
//    if (v->p >= 0 && v->p <= v->l) 														/* MAYBE IT CAN BE NEEDED IN FUTURE ? STAY : DELL */
	if (!v->zer)
		v->p <= v->l ? v->p = 0 : (v->p -= v->l);
	else if (v->zer)
		v->p = (v->w - v->l - v->spa - v->min - v->pl) < 0 ? 0
														   : v->w - v->l - v->spa - v->min - v->pl;
    if (v->w >= 0)
    	v->w <= v->l ? (v->w = 0) : (v->w -= (v->l + v->spa + v->p + v->min + v->pl));

	f_part_two(v, v_arg, argv);
    return (1);
}

static int 		f_part_two(t_var *v, long long int v_arg, char *argv)
{
 if (v->w >= 0)
	{
		if (v->zer)
			v->bp += f_w_e_l('0', v->w);
		else
			v->bp += f_w_e_l(' ', v->w);
	}
    if (v->w < 0)
	{
		if ((v_arg >= 0 && v->min) && (v->min = 0))
			;
		(v->w * -1) <= v->l ? (v->w = 0)
							: (v->w = (v->w * -1) - (v->l + v->spa + v->p + v->min + v->pl));
	}
    v->bp += f_w_e_l(' ', v->spa);
    v->bp += f_w_e_l('-', v->min);
	v->bp += f_w_e_l('+', v->pl);
    v->bp += f_w_e_l('0', v->p);
    v->bp += write(1, argv, v->l);
    if (v->tmp < 0)
    	v->bp += f_w_e_l(' ', v->w);
	return (1);
}
