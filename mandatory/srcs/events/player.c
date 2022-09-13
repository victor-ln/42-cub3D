/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:00:58 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/12 23:34:59 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calculate_next_step(t_game *game, int move_step, int side_step);
static int	diagonal_colision(t_game *game, double to_x, double to_y);

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

static void	calculate_next_step(t_game *game, int move_step, int side_step)
{
	double	to_x;
	double	to_y;
	double	angle;
	int		margin_x;
	int		margin_y;

	angle = game->player.coord.angle;
	to_x = (cos(angle) * move_step) + (cos(angle + HALF_PI) * side_step);
	to_y = (sin(angle) * move_step) + (sin(angle + HALF_PI) * side_step);
	margin_x = 16;
	margin_y = 16;
	if (to_x < 0)
		margin_x = -16;
	if (to_y < 0)
		margin_y = -16;
	to_x += game->player.coord.x;
	to_y += game->player.coord.y;
	if (!has_wall_at(game, to_x + margin_x, to_y + margin_y) && \
		!diagonal_colision(game, to_x + margin_x, to_y + margin_y))
	{
		game->player.coord.x = to_x;
		game->player.coord.y = to_y;
	}
}

static int	diagonal_colision(t_game *game, double to_x, double to_y)
{
	double		x_diff;
	double		y_diff;

	x_diff = to_x - game->player.coord.x;
	y_diff = to_y - game->player.coord.y;
	if (fabs(x_diff) <= TILE_SIZE && fabs(y_diff) <= TILE_SIZE)
	{
		if (has_wall_at(game, to_x - x_diff, to_y))
			return (1);
		if (has_wall_at(game, to_x, to_y - y_diff))
			return (1);
	}
	return (0);
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
