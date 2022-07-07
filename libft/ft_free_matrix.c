/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:09:26 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/06 17:10:04 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(void **matrix, size_t size)
{
	int	i;

	i = -1;
	if (size)
	{
		while (++i < size)
			ft_free_null(matrix[i]);
	}
	else
		while (matrix[++i])
			ft_free_null(matrix[i]);
}
