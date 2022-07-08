/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:09:26 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/07 19:19:11 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(void **matrix, size_t size)
{
	size_t	i;

	i = -1;
	if (size)
	{
		while (++i < size)
			ft_free_null(matrix[i]);
	}
	else
		while (matrix[++i])
			ft_free_null(matrix[i]);
	ft_free_null(matrix);
}
