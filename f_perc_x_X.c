//
// Created by Nikolay MIZIN on 4/9/18.
//

#include "ft_printf.h"

static int		f_find_weight(const char **format, char c, va_list ap, t_var *v);
static int		f_find_precision(const char **format, char c, va_list ap);
static int 		f_width(t_var *v, unsigned long long int v_arg);
//static int      f_if_u_U(t_var *v, unsigned long long int *v_arg, va_list ap);

int     f_perc_x_X(va_list ap, const char **format, t_var *v)
{
    unsigned long long int	v_arg;
    char                   *argv;
    char                    tmp;

    (tmp = v->res) && (v->ts == l && v->res == 'U') && (tmp = 'u');
    f_sign(format, v);
    v->w = f_find_weight(format, tmp, ap, v);
    v->p = f_find_precision(format, tmp, ap);
    if (v->res == 'U' || (v->res == 'u' && (v->ts == l || v->ts == j)))
        v_arg  = va_arg(ap, unsigned long);
    else if ((v->res == 'u' && v->ts != ll) || (v->hes && (v->ts != l && v->ts != ll)))
        v_arg  = va_arg(ap, unsigned);
    else if (v->ts != l && v->ts != ll && v->ts != j)
//    if (v->ts != l && v->ts != ll && v->ts != j) /* DELL */
        v_arg  = va_arg(ap, unsigned);
    else
        v_arg  = va_arg(ap, unsigned long long int);
    f_spec_the_size_for_x_and_X(&v_arg, v);
    (v->l = f_width(v, v_arg));
    if (v->res == 'u' || v->res == 'U')
        argv = ft_itoa_base(v_arg, 10, v->res);
    else
        argv = ft_itoa_base(v_arg, 16, v->res);
    f_handl_x_X(v, v_arg, argv);
    while (**format != tmp)
        (*format)++;
    (**format != '\0') && (*format)++;
    free(argv);
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

static int 		f_width(t_var *v,unsigned long long int v_arg)
{
    int count;

    count = 0;
    if (v->res == 'x' || v->res == 'X')
    {
        if (v_arg == 0)
            count++;
        while (v_arg)
            ++count && (v_arg /= 16);
        return (count);
    }
    else
    {
        if (v_arg == 0)
            count++;
        while (v_arg)
            ++count && (v_arg /= 10);
        return (count);
    }

}

//static int      f_if_u_U(t_var *v, unsigned long long int *v_arg, va_list ap)
//{
//    if (v->res == 'U' )
//        v_arg  = va_arg(ap, unsigned long);
//    else if (v->res == 'u' || (v->hes && (v->ts != l && v->ts != ll)))
//        v_arg  = va_arg(ap, unsigned);
//    return (1);
//}