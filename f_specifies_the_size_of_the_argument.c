//
// Created by Nikolay MIZIN on 4/9/18.
//

#include "ft_printf.h"

int     f_spec_the_size_for_d_and_i(long long int *v_arg, t_var *v)
{
    if (v->ts == l || v->res == 'D')
        (*v_arg) = (long)(*v_arg);
    else if (v->ts == h)
        (*v_arg) = (short)(*v_arg);
    else if (v->ts == hh)
        (*v_arg) = (char)(*v_arg);
    else if (v->ts == j)
        (*v_arg) = (intmax_t)(*v_arg);
    else if (v->ts == z)
            (*v_arg) = (size_t)(*v_arg);
    return (1);
}

int     f_spec_the_size_for_x_and_X(unsigned long long int *v_arg, t_var *v)
{
    if (v->ts == l || v->res == 'O' || v->res == 'U')
        (*v_arg) = (unsigned long)(*v_arg);
    else if (v->ts == h)
        (*v_arg) = (unsigned short)(*v_arg);
    else if (v->ts == hh)
        (*v_arg) = (unsigned char)(*v_arg);
    else if (v->ts == j)
        (*v_arg) = (uintmax_t)(*v_arg);
    else if (v->ts == z)
        (*v_arg) = (size_t)(*v_arg);
    return (1);
}


