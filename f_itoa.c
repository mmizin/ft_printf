//
// Created by mizman on 05.04.18.
//
#include "ft_printf.h"

int     f_len(int number)
{
    int count;

    count = 0;
    if (number == 0)
        count++;
    while (number)
    {
        count++;
        number /= 10;
    }
    return (count);
}

char    *f_itoa(int number)
{
    int len;
    long int num;
    char *new;

    num = (long int) number;
    len = f_len(number);
    if (!(new = (char *) malloc(sizeof(char) * (len + 1))))
        return (NULL);
    new[len] = '\0';
    if (num < 0)
        (num = -num);
    new[--len] = num % 10 + '0';
    while (num /= 10)
        new[--len] = num % 10 + '0';
    return (new);
}
