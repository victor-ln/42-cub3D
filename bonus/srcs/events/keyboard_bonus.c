/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:24:32 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/08 20:25:34 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	key_movement(int keycode, t_game *game);

int	key_press_game(int keycode, t_game *game)
{
	if (!game->is_on_the_game)
		return (key_press_menu(keycode, game));
	key_movement(keycode, game);
	if (keycode && ft_strchr("1234", keycode))
		game->player.weapon = keycode - '0' - 1;
	else if (keycode == TAB)
		game->show_full_map = !game->show_full_map;
	else if (keycode == 'm' && \
		game->window_width >= 720 && game->window_height >= 480)
	{
		game->is_on_the_game = false;
		change_menu(&game->menu, SELECTION_MENU);
	}
	else if (keycode == CTRL)
	{
		game->player.is_shooting = true;
		game->player.has_shooted = false;
	}
	else if (keycode == 'e')
		open_door(game);
	else if (keycode == SHIFT)
		game->player.movement_speed = 16;
	else if (keycode == ESC)
		end_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (!game->is_on_the_game)
		return (0);
	if (keycode == ARROW_RIGHT)
		game->player.move_direction = 0;
	else if (keycode == ARROW_LEFT)
		game->player.move_direction = 0;
	else if (keycode == 'd')
		game->player.side_direction = 0;
	else if (keycode == 'a')
		game->player.side_direction = 0;
	else if (keycode == 's')
		game->player.walk_direction = 0;
	else if (keycode == 'w')
		game->player.walk_direction = 0;
	else if (keycode == CTRL && game->player.has_shooted)
		game->player.is_shooting = false;
	else if (keycode == SHIFT)
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
		game->player.side_direction = WALK_LEFT;
	else if (keycode == 'd')
		game->player.side_direction = WALK_RIGHT;
	else if (keycode == 's')
		game->player.walk_direction = WALK_DOWN;
	else if (keycode == 'w')
		game->player.walk_direction = WALK_UP;
}
