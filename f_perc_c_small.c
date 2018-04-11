//
// Created by mizman on 04.04.18.
//

#include "ft_printf.h"

static	int		f_find_weight(const char **format, char c, va_list ap);
static	int		f_if_handler(t_var *v, va_list ap);

int     f_perc_c_small(va_list ap, const char **format, t_var *v)
{
    v->w = f_find_weight(format, 'c', ap);
    f_if_handler(v, ap);
    (**format != '\0') && (*format)++;
    f_reset_init(v);
    return (1);
}

static	int		f_find_weight(const char **format, char c, va_list ap)
{
    int		width;
    int		sign;

    sign = 1;
    while (format && **format != c)
    {
        if (**format == '-')
            sign = -1;
        if (**format == '*')
        {
            width = va_arg(ap, unsigned int);
            width = width < 0 ? width : width * sign;
            return (width);
        }
        if (**format >= '1' && **format <= '9')
        {
            width = ft_atoi(*format) * sign;
            while (**format >= '0' && **format <= '9')
                (*format)++;
            return (width);
        }
        (**format != c) && (*format)++;
    }
    return (0);
}

static	int		f_if_handler(t_var *v, va_list ap)
{
    int tmp;
    unsigned char c;

    c = va_arg(ap, unsigned int);
    if (v->w >= 1)
        v->w -= 1;
    if (v->w < 0)
        tmp = (v->w * -1) > 1 ? (v->w * -1) - 1 : 0;
    if (v->w >= 0)
    {
        v->bp += f_w_e_l(' ', v->w);
        v->bp += write(1, &c, 1);
    }
    else if (v->w < 0)
    {
        v->bp += write(1, &c, 1);
        v->bp += f_w_e_l(' ', tmp);
    }
    return (1);
}