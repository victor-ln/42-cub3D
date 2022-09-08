/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:00:58 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 21:27:16 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_game *game)
{
	double	move_step;
	double	to_x;
	double	to_y;
	double	angle;
	int		walk_direction;

	game->player.coord.angle += game->player.move_direction * \
		game->player.rotation_speed;
	normalize_angle(&game->player.coord.angle);
	angle = game->player.coord.angle;
	walk_direction = game->player.walk_direction;
	if (game->player.walk_direction == WALK_LEFT || \
		game->player.walk_direction == WALK_RIGHT)
	{
		walk_direction /= 2;
		angle += M_PI_2;
	}
	move_step = walk_direction * game->player.movement_speed;
	to_x = game->player.coord.x + (cos(angle) * move_step);
	to_y = game->player.coord.y + (sin(angle) * move_step);
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
