/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:00:58 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/08 18:22:14 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	calculate_fov(t_player *player);
static void	calculate_next_step(t_game *game, int move_step, int side_step);

void	move_player(t_game *game)
{
	int		move_step;
	int		side_step;

	if (game->player.move_direction)
		calculate_fov(&game->player);
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

static void	calculate_fov(t_player *player)
{
	player->coord.angle += player->move_direction * \
		player->rotation_speed;
	normalize_angle(&player->coord.angle);
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
	if (!has_wall_at(game, to_x + margin_x, to_y + margin_y))
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
	if (y < 0 || y > game->minimap.height * TILE_SIZE || x < 0 || \
		x > ft_strlen(game->params.map[line]) * TILE_SIZE)
		return (1);
	if (game->params.map[line][column] == 'D')
		return (1);
	else if (game->params.map[line][column] == 'O')
		return (0);
	else if (game->params.map[line][column] == 'e')
		return (0);
	return (game->params.map[line][column] != '0' && \
		game->params.map[line][column] != ' ');
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
