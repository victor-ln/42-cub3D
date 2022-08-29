/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 04:19:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/08/08 04:19:28 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int number)
{
	int	size;

	size = 0;
	if (number == 0)
		return (1);
	if (number < 1)
		size++;
	while (number)
	{
		number /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	long	temp;
	size_t	size;

	temp = nbr;
	size = ft_size(nbr);
	if (temp < 0)
		temp = -temp;
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	*(str + size--) = '\0';
	while (temp > 0)
	{
		*(str + size--) = temp % 10 + '0';
		temp /= 10;
	}
	if (size == 0 && str[1] == '\0')
		*(str + size) = '0';
	else if (size == 0 && str[1] != '\0')
		*(str + size) = '-';
	return (str);
}
