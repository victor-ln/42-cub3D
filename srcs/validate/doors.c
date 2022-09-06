/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:57:33 by afaustin          #+#    #+#             */
/*   Updated: 2022/08/31 20:54:48 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	doors_validate(t_game *game)
{
	int		line;
	int		column;
	char	**map;

	map = game->params.map;
	line = -1;
	while (map[++line])
	{
		column = -1;
		while (map[line][++column])
		{
			if (map[line][column] != 'D')
				continue ;
			if (map[line][column + 1] == '1' && map[line][column - 1] == '1')
				continue ;
			if (map[line - 1][column] == '1' && map[line + 1][column] == '1')
				continue ;
			error("The door must be between two facing walls", game);
		}
	}
}
