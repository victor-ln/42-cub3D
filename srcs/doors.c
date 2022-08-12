/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:57:33 by afaustin          #+#    #+#             */
/*   Updated: 2022/08/11 21:44:55 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	save_doors_coordinates(t_game *game);
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
	game->doors = malloc(sizeof(t_doors) * game->doors_num);
	if (!game->doors)
		error("Malloc Failed", game);
	doors_validate(game);
	save_doors_coordinates(game);	
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

static void	save_doors_coordinates(t_game *game)
{
	int		line;
	int		column;
	int		counter;
	char	**map;

	map = game->params.map;
	line = -1;
	counter = 0;
	while (map[++line])
	{
		column = -1;
		while (map[line][++column])
		{
			if (map[line][column] == 'D')
			{
				game->doors[counter].status = CLOSED;
				game->doors[counter].x = column;
				game->doors[counter].y = line;
				counter++;
			}			
		}
	}
}

int		open_door(t_game *game)
{
	double	angle;
	int		to_x;
	int		to_y;
	// int		i;
	double	move_step;

	move_step = 16 * MOVEMENT_SPEED;
	angle = game->player.coord.angle;
	to_x = (game->player.coord.x + (cos(angle) * move_step)) / TILE_SIZE;
	to_y = (game->player.coord.y + (sin(angle) * move_step)) / TILE_SIZE;
	// i = 0;
	if (game->params.map[to_y][to_x] == 'D')
	{
		// while (i < game->doors_num)
		// {
		// 	if (game->doors[i].x == to_x && game->doors[i].y == to_y)
		// 	{
		// 		if (game->doors[i].status == CLOSED)
		// 			game->doors[i].status = OPEN;
		// 		else
		// 			game->doors[i].status = CLOSED;
		// 		break ;
		// 	}
		// 	i++;
		// }
		game->params.map[to_y][to_x] = 'O';
	}
	else if (game->params.map[to_y][to_x] == 'O')
		game->params.map[to_y][to_x] = 'D';
	return (0);
}