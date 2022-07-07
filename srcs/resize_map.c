/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 22:02:27 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/06 22:02:419 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static void	shift_back_matrix(char **ptr);

void	resize_map(t_game *game)
{
	int		i;
	int		j;
	int		walls;
	int		spaces;
	int		len;

	i = 0;
	while (game->params.map[i])
	{
		j = 0;
		walls = 0;
		spaces = 0;
		len = ft_strlen(game->params.map[i]);
		while ((j + spaces) < len)
		{
			while (ft_isspace(game->params.map[i][j + spaces]))
				spaces++;
			if (game->params.map[i][j + spaces] == '1')
				walls++;
			j++;
		}
		if (walls == 1 && spaces - j == 1)
			shift_back_matrix(game->params.map + i);
		else
			i++;
	}
}

static void	shift_back_matrix(char **ptr)
{
	int	i;

	i = 0;
	free(ptr[i]);
	while (ptr[i])
	{
		ptr[i] = ptr[i + 1];
		i++;
	}
}
