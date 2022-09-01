/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:24:32 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/01 18:40:24 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	key_movement(int keycode, t_game *game);

int	key_press(int keycode, t_game *game)
{
	key_movement(keycode, game);
	if (ft_strchr("1234", keycode))
		game->player.weapon = keycode - '0' - 1;
	else if (keycode == ESC)
		end_game(game);
	else if (keycode == CTRL)
	{
		game->player.is_shooting = true;
		game->player.has_shooted = false;
	}
	else if (keycode == 'e')
		open_door(game);
	else if (keycode == ALT)
		game->player.movement_speed = 16;
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
	else if (keycode == CTRL)
		game->player.is_shooting = false;
	else if (keycode == ALT)
		game->player.movement_speed = 8;
	return (0);
}

static void	key_movement(int keycode, t_game *game)
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
}
