/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:57:33 by afaustin          #+#    #+#             */
/*   Updated: 2022/08/16 21:01:48 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	doors_validate(t_game *game);

void	save_doors_params(t_game *game)
{
	int		line;
	char	**map;

	line = -1;
	map = game->params.map;
	game->doors_num = 0;
	while (map[++line])
		game->doors_num += ft_count_char(map[line], 'D');
	if (!game->doors_num)
		return ;
	doors_validate(game);
}

static void	doors_validate(t_game *game)
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

int		open_door(t_game *game)
{
	double	angle;
	int		to_x;
	int		to_y;
	double	move_step;

	move_step = 16 * MOVEMENT_SPEED;
	angle = game->player.coord.angle;
	to_x = (game->player.coord.x + (cos(angle) * move_step)) / TILE_SIZE;
	to_y = (game->player.coord.y + (sin(angle) * move_step)) / TILE_SIZE;
	if (game->params.map[to_y][to_x] == 'D')
		game->params.map[to_y][to_x] = 'O';
	else if (game->params.map[to_y][to_x] == 'O')
		game->params.map[to_y][to_x] = 'D';
	return (0);
}
