/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmizin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:01:29 by nmizin            #+#    #+#             */
/*   Updated: 2017/11/22 19:07:45 by nmizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *str)
{
	unsigned long int	out;
	int					minus;

	minus = 1;
	out = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str >= '0' && *str <= '9')
	{
		if ((out > 922337203685477580 || (out == 922337203685477580
		&& (*str - '0') > 7)) && minus == 1)
			return (-1);
		else if ((out > 922337203685477580 || (out == 922337203685477580
			&& (*str - '0') > 8)) && minus == -1)
			return (0);
		out = out * 10 + (*str - 48);
		str++;
	}
	return ((int)out * minus);
}
