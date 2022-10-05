/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 19:30:01 by afaustin          #+#    #+#             */
/*   Updated: 2022/10/04 20:30:16 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_charaters(char *str, char *characters)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (ft_strchr(characters, str[i]))
			counter++;
		i++;
	}
	return (counter);
}
