//
// Created by mizman on 05.04.18.
//
#include "ft_printf.h"

int     f_len(long long int number)
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

char    *f_itoa(long long int number)
{
    int len;
    char *new;

    len = f_len(number);
    if (!(new = (char *) malloc(sizeof(char) * (len + 1))))
        return (NULL);
    new[len] = '\0';
    new[--len] = number % 10 < 0 ? -1 * (number % 10) + '0' : number % 10 + '0';
    while (number /= 10)
    {
        number = number < 0 ? -number : number;
        new[--len] = number % 10 + '0';
    }

    return (new);
}
