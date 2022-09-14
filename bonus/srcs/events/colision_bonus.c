/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:02:04 by afaustin          #+#    #+#             */
/*   Updated: 2022/09/13 22:22:18 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	diagonal_colision(t_game *game, double to_x, double to_y);
static int	enemy_colision(t_game *game, double to_x, double to_y);

void	calculate_next_step(t_game *game, int move_step, int side_step)
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
		!diagonal_colision(game, to_x + margin_x, to_y + margin_y) && \
		!enemy_colision(game, to_x, to_y))
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
	if (x_diff && y_diff)
	{
		return (has_wall_at(game, to_x - x_diff, to_y) || \
			has_wall_at(game, to_x, to_y - y_diff));
	}
	return (0);
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
	return (game->params.map[line][column] == '1');
}

static int	enemy_colision(t_game *game, double to_x, double to_y)
{
	int		i;
	int		sprite_index;
	double	new_hipo;

	i = -1;
	while (++i < game->closest_sprites_num)
	{
		sprite_index = game->closest_sprites[i];
		new_hipo = calculate_hipo(game->sprites[sprite_index].coord.x - to_x, \
			game->sprites[sprite_index].coord.y - to_y);
		if (new_hipo <= 16)
			return (1);
	}
	return (0);
}
