//
// Created by mizman on 03.04.18.
//

#include "ft_printf.h"

static	int		f_find_weight(const char **format, char c, va_list ap);
static	int		f_find_precision(const char **format, char c, va_list ap);
static	int		f_if_handler(t_var *v, const char *format);

int     f_from_per_to_per(va_list ap, const char **format, t_var *v)
{
    v->l = 0;
    *format = v->begin;
    v->w = f_find_weight(format, '%', ap);
    v->p = f_find_precision(format, '%', ap);
    v->begin = *format;
    while (*format && **format && **format != '%')
        (*format)++ && v->l++;
    (**format == '%') && v->l++;
    (v->p == 257) && (v->p = v->l);
    f_if_handler(v, *format);
    if (**format == '%')
        return (1);
    else
        return (0);
}

static	int		f_find_weight(const char **format, char c, va_list ap)
{
    int		width;
    int		sign;

    sign = 1;
    while (format && **format != c && **format != '.')
    {
        if (**format == '-')
            sign = -1;
        if (**format == '*')
        {
            width = va_arg(ap, int);
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
        (**format != c && **format != '.') && (*format)++;
    }
    return (0);
}

static	int		f_find_precision(const char **format, char c, va_list ap)
{
    int		prec;
    int		point;

    prec = 0;
    point = 0;
    while (**format && **format != c)
    {
        if ((**format == '.') && ++point)
        {
            if (*(*format + 1) == '*')
                prec = va_arg(ap, int);
            if ((*(*format + 1) >= '0' && *(*format + 1) <= '9') && (*format)++)
            {
                prec = ft_atoi(*format);
                while (**format && (**format >= '0' && **format <= '9'))
                    (*format)++;
                return (prec);
            }
        }
        (**format != c) && (*format)++;
    }
    if (!point)
        return (257);
    return (prec);
}

static	int		f_if_handler(t_var *v, const char *format)
{
    int tmp;

    if (v->p >= v->l && *format == '%')
        v->l--;
    if (v->p == 0 || v->p <= v->l)
        v->l = v->p;
    if (v->w >=0 && v->w <= v->l)
        v->w = v->l;
    if (v->w < 0)
        tmp = (v->w * -1) > v->l ? (v->w * -1) - v->l : 0;
    if (v->w >= 0 && v->w >= v->l)
    {
        v->bp += f_w_e_l(' ', v->w - v->l);
        v->bp += write(1, v->begin, v->l);
        (*format == '%') && (v->bp += write(1, "%", 1));
    }
    else if (v->w < 0)
    {
        v->bp += write(1, v->begin, v->l);
        (*format == '%') && (v->bp += write(1, "%", 1));
        v->bp += f_w_e_l(' ', tmp);
    }
    return (1);
}