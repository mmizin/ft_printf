//
// Created by mizman on 04.04.18.
//

#include "ft_printf.h"

static int		f_find_weight(const char **format, char c, va_list ap, t_var *v);
static int		f_find_precision(const char **format, char c, va_list ap);
static int 		f_width(long long int v_arg);

int         	f_perc_d_small(va_list ap, const char **format, t_var *v)
{
	long long int	v_arg;
	char			*argv;
    char            tmp;

    (tmp = v->res) && (v->ts == l && v->res == 'D') && (tmp = 'd');
    f_sign(format, v);
    f_sign(format, v);
	v->w = f_find_weight(format, tmp, ap, v);
	if ((v->min && v->w > 0) && (v->w *= -1))
		;
	v->p = f_find_precision(format, tmp, ap);
	if (v->ts != l && v->ts != ll && v->ts != j && v->res != 'D')
        v_arg  = va_arg(ap, int);
	else
		v_arg  = va_arg(ap, long long int);
	f_spec_the_size_for_d_and_i(&v_arg, v);
	v->l = f_width(v_arg);
	argv = f_itoa(v_arg);
	f_for_d_and_i_flags(v, v_arg, argv);
	free(argv);
	while (**format != tmp)
		(*format)++;
	(**format != '\0') && (*format)++;
	f_reset_init(v);
    return (1);
}

static int		f_find_weight(const char **format, char c, va_list ap, t_var *v)
{
	int		sign;

	sign = 1;
	while (format && **format != c && **format != '.')
	{
		if (**format == '-' && (sign = -1))
			;
		if (**format == '*')
		{
			(v->w = va_arg(ap, int)) && (v->w = v->w < 0 ? v->w : v->w * sign);
			return (v->w);
		}
		if (**format >= '1' && **format <= '9')
		{
			v->w = ft_atoi(*format) * sign;
			while ((**format >= '0' && **format <= '9'))
				(*format)++;
			return (v->w);
		}
		(**format != c && **format != '.') && (*format)++;
	}
	return (0);
}

static	int		f_find_precision(const char **format, char c, va_list ap)
{
    int res;
	int check;

    while (**format && **format != c)
	{
		if (**format == '.')
		{
			check = 1;
			if (**format == '*')
				return (va_arg(ap, int));
			if (*(*format + 1) >= '0' && *(*format + 1) <= '9')
			{
				res = ft_atoi(++(*format));
				while (**format >= '0' && **format <= '9')
					(*format)++;
				return (res);
			}
		}
		(*format)++;
	}
	if (check == 1)
		return (0);
    else
		return (-1);
}

static int 		f_width(long long int v_arg)
{
    int count;

	count = 0;
	if (v_arg == 0)
		count++;
	while (v_arg)
		++count && (v_arg /= 10);
	return (count);
}
