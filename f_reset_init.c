//
// Created by Nikolay MIZIN on 4/10/18.
//

#include "ft_printf.h"

int     f_reset_init(t_var *v)
{
    v->p = -1;
    v->w = 0;
    v->l = 0;
    v->c = 0;
    v->cur_max = 0;
    v->i = 0;
    v->sign = 0;
    v->begin = NULL;
    v->pl = 0;
    v->min = 0;
    v->hes = 0;
    v->spa = 0;
    v->zer = 0;
    v->tmp = 0;
    v->ts = 192;
    return (1);
}