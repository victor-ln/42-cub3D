/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:04:56 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/11 18:05:00 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	x;
	int				i;

	x = 0;
	i = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
			|| *str == '\r' || *str == '\t' || *str == '\v')
			str++;
	if (*str == '-' || *str == '+')
	{
			if (*str == '-')
					i *= -1;
			str++;
	}
	while (*str >= '0' && *str <= '9')
	{
			x = x * 10 + *str - '0';
			str++;
	}
	return ((int)(x *= i));
}
