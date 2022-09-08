/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:24:58 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 20:43:54 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	swap(t_sprites *x, t_sprites *y);
static int	partition(t_sprites *sprites, int start, int end);

void	qsort_recursive(t_sprites *sprites, int start, int end)
{
	int		pivot_index;

	if (start >= end)
		return ;
	pivot_index = partition(sprites, start, end);
	qsort_recursive(sprites, start, pivot_index - 1);
	qsort_recursive(sprites, pivot_index + 1, end);
}

int	partition(t_sprites *sprites, int start, int end)
{
	int			i;
	t_sprites	*pivot;
	int			pivot_index;

	i = start;
	pivot = sprites + end;
	pivot_index = start;
	while (i < end)
	{
		if (sprites[i].coord.hipo >= pivot->coord.hipo)
		{
			swap(&sprites[i], &sprites[pivot_index]);
			pivot_index++;
		}
		i++;
	}
	swap(&sprites[end], &sprites[pivot_index]);
	return (pivot_index);
}

static void	swap(t_sprites *x, t_sprites *y)
{
	t_sprites	z;

	z = *x;
	*x = *y;
	*y = z;
}
