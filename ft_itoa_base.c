/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 12:05:21 by exam              #+#    #+#             */
/*   Updated: 2018/03/13 13:17:39 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int f_size(unsigned long long int num, int base)
{
	int count;

	count = 0;
	if (num == 0)
		count++;
	while (num)
	{
		count++;
		num /= base;
	}
	return (count);
}

char	*ft_itoa_base(unsigned long long int value, int base, char res)
{
	unsigned long long int num;
	char *new;
	int size;

	num = value;
	size = f_size(num, base);
	new = (char *)malloc(sizeof(char) * (size + 1));
	new[size] = '\0';
	new[--size] = num % base >= 10 ? (num % base - 10) + 'A' : (num % base) + '0';
	while (num /= base)
		new[--size] = num % base >= 10 ? (num % base - 10) + 'A' : (num % base) + '0';
	if (res == 'x' || res == 'p')
	{
		size = 0;
		while (new[size])
		{
			if (new[size] >= 'A' && new[size] <= 'Z')
				new[size] += 32;
			size++;
		}
	}
	return (new);
}
