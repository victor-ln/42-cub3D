/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:00:58 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/13 21:02:45 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	move_player(t_game *game)
{
	int		move_step;
	int		side_step;

	if (game->player.move_direction)
	{
		game->player.coord.angle += game->player.move_direction * \
			game->player.rotation_speed;
		normalize_angle(&game->player.coord.angle);
	}
	if (game->player.side_direction || game->player.walk_direction)
	{
		move_step = game->player.walk_direction * game->player.movement_speed;
		side_step = game->player.side_direction * game->player.movement_speed;
		if (game->player.side_direction && game->player.walk_direction)
		{
			move_step /= 2;
			side_step /= 2;
		}
		calculate_next_step(game, move_step, side_step);
	}
}

void	open_door(t_game *game)
{
	double	angle;
	int		to_x;
	int		to_y;
	double	move_step;

	move_step = TILE_SIZE;
	angle = game->player.coord.angle;
	to_x = (game->player.coord.x + (cos(angle) * move_step)) / TILE_SIZE;
	to_y = (game->player.coord.y + (sin(angle) * move_step)) / TILE_SIZE;
	if (game->params.map[to_y][to_x] == 'D')
		game->params.map[to_y][to_x] = 'O';
	else if (game->params.map[to_y][to_x] == 'O')
		game->params.map[to_y][to_x] = 'D';
}
