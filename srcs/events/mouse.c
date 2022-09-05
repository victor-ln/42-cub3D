/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:24:58 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/05 20:49:59 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)x, (void)y;
	if (!game->is_on_the_game)
		return (0);
	if (button == LEFT_CLICK)
	{
		game->player.is_shooting = true;
		game->player.has_shooted = false;
	}
	else if (button == RIGHT_CLICK)
		open_door(game);
	else if (button == SCROLL_UP)
	{
		if (game->player.weapon)
			game->player.weapon--;
		else
			game->player.weapon = WEAPONS_TYPES - 1;
	}
	else if (button == SCROLL_DOWN)
	{
		if (game->player.weapon < WEAPONS_TYPES - 1)
			game->player.weapon++;
		else
			game->player.weapon = 0;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)x, (void)y;
	if (!game->is_on_the_game)
		return (0);
	if (button == LEFT_CLICK && game->player.has_shooted)
	{
		game->player.is_shooting = false;
		game->player.has_shooted = false;
	}
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int		last_x = -1;
	static float	move_direction;

	(void)y;
	if (!game->is_on_the_game)
		return (0);
	mlx_mouse_get_pos(game->mlx, game->window, &x, &y);
	if (last_x != x)
	{
		move_direction = (x- (game->half_width)) * 0.001;
		game->player.coord.angle += move_direction * \
			game->player.rotation_speed;
		move_direction = 0;
		last_x = x;
	}
	return (0);
}
