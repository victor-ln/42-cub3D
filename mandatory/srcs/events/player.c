/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:00:58 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 22:11:25 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_game *game)
{
	int		move_step;
	double	to_x;
	double	to_y;
	double	angle;
	int		side_step;

	move_step = game->player.walk_direction * game->player.movement_speed;
	side_step = game->player.side_direction * game->player.movement_speed;
	angle = game->player.coord.angle;
	to_x = 0;
	to_y = 0;
	game->player.coord.angle += game->player.move_direction * \
		game->player.rotation_speed;
	normalize_angle(&game->player.coord.angle);
	if (game->player.side_direction && game->player.walk_direction)
	{
		move_step /= 2;
		side_step /= 2;
	}
	if (game->player.walk_direction)
	{
		to_x = (cos(angle) * move_step);
		to_y = (sin(angle) * move_step);
	}
	if (game->player.side_direction)
	{
		to_x += (cos(angle + M_PI_2) * side_step);
		to_y += (sin(angle + M_PI_2) * side_step);
	}
	to_x += game->player.coord.x;
	to_y += game->player.coord.y;
	if (!has_wall_at(game, to_x, to_y))
	{
		game->player.coord.x = to_x;
		game->player.coord.y = to_y;
	}
}

int	has_wall_at(t_game *game, double x, double y)
{
	int	column;
	int	line;

	column = (int)floor((x / TILE_SIZE));
	line = (int)floor((y / TILE_SIZE));
	if (y < 0 || y > game->minimap_heightpx || x < 0 || \
		x > ft_strlen(game->params.map[line]) * TILE_SIZE)
		return (1);
	return (game->params.map[line][column] == '1');
}
