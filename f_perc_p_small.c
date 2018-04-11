//
// Created by Nikolay MIZIN on 4/11/18.
//

#include "ft_printf.h"

int     f_perc_p_small(va_list ap, const char **format, t_var *v)
{
    void    *x;
    char    *res;
    int     i;

    x = va_arg(ap, void *);
    res = ft_itoa_base((unsigned long long)x, 16, v->res);
    i = ft_strlen(res);
    (v->bp =+ write(1, "0x", 2)) && (v->bp += write (1, res, i));
    while (**format != v->res)
        (*format)++;
    (**format != '\0') && (*format)++;
    return (1);
}