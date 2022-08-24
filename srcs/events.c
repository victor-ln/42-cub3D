/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:18:14 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:18:14 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_player(t_game *game);

int	key_press(int keycode, t_game *game)
{
	if (keycode == ARROW_RIGHT)
		game->player.move_direction = TURN_RIGHT;
	else if (keycode == ARROW_LEFT)
		game->player.move_direction = TURN_LEFT;
	else if (keycode == 'a')
		game->player.walk_direction = WALK_LEFT;
	else if (keycode == 'd')
		game->player.walk_direction = WALK_RIGHT;
	else if (keycode == 's')
		game->player.walk_direction = WALK_DOWN;
	else if (keycode == 'w')
		game->player.walk_direction = WALK_UP;
	else if (ft_strchr("1234", keycode))
		game->player.weapon = keycode - '0' - 1;
	else if (keycode == ESC)
		end_program(game);
	else if (keycode == CTRL)
		game->player.is_shoting = 1;
	else if (keycode == 'e')
		return (open_door(game));
	else
		return (0);
	move_player(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == ARROW_RIGHT)
		game->player.move_direction = 0;
	else if (keycode == ARROW_LEFT)
		game->player.move_direction = 0;
	else if (keycode == 'd')
		game->player.walk_direction = 0;
	else if (keycode == 'a')
		game->player.walk_direction = 0;
	else if (keycode == 's')
		game->player.walk_direction = 0;
	else if (keycode == 'w')
		game->player.walk_direction = 0;
	return (0);
}

int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLICK)
		game->player.is_shoting = 1;
		// shot(game);
	// if (button == RIGHT_CLICK)
		// open_door
	if (button == SCROLL_UP)
	{
		// change weapon
		if (game->player.weapon)
			game->player.weapon--;
		else
			game->player.weapon = WEAPONS_TYPES - 1;
	}
	if (button == SCROLL_DOWN)
	{
		if (game->player.weapon < WEAPONS_TYPES - 1)
			game->player.weapon++;
		else
			game->player.weapon = 0;
		// change weapon
	}
	return (0);
}

static void	move_player(t_game *game)
{
	double	move_step;
	double	to_x;
	double	to_y;
	double	angle;

	game->player.coord.angle += game->player.move_direction * \
		game->player.rotation_speed;
	normalize_angle(&game->player.coord.angle);
	angle = game->player.coord.angle;
	if (game->player.walk_direction == WALK_LEFT || \
		game->player.walk_direction == WALK_RIGHT)
	{
		game->player.walk_direction /= 2;
		angle += M_PI_2;
	}
	move_step = game->player.walk_direction * MOVEMENT_SPEED;
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
