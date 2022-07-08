/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_vectors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:41:08 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/07 19:35:46 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

size_t	ft_count_vectors(void **matrix)
{
	size_t	i;
	
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
