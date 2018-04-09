//
// Created by Nikolay MIZIN on 4/9/18.
//

#include "ft_printf.h"

int     f_spec_the_size_for_d_and_i(long long int *v_arg, t_var *v)
{
    if (v->ts == l)
        (*v_arg) = (long)(*v_arg);
    else if (v->ts == h)
        (*v_arg) = (short)(*v_arg);
    else if (v->ts == hh)
        (*v_arg) = (char)(*v_arg);
    else if (v->ts == j)
        (*v_arg) = (intmax_t)(*v_arg);
    return (1);
}