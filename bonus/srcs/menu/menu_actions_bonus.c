/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_actions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:52:17 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 20:43:54 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	change_menu(t_menu *menu, t_menu_screen menu_screen)
{
	menu->menu_index = 0;
	menu->menu_screen = menu_screen;
}

void	apply_changes(t_game *game)
{
	if (game->menu.menu_index >= RESOLUTION_SELECTED_1)
	{
		if (set_resolution(game) == EXIT_SUCCESS)
			game->mlx->end_loop = true;
		game->menu.menu_index = RESOLUTION;
		game->half_width = game->window_width / 2;
		game->half_height = game->window_height / 2;
		game->wall_prop.proj_wall_dist = game->half_width / tan(FOV_ANGLE / 2);
	}
	else
	{
		if (game->menu.menu_index == MOUSE_SPEED_SELECTED_1)
			game->player.rotation_speed = STD_ROTATION_SPEED_1;
		else if (game->menu.menu_index == MOUSE_SPEED_SELECTED_2)
			game->player.rotation_speed = STD_ROTATION_SPEED_2;
		else if (game->menu.menu_index == MOUSE_SPEED_SELECTED_3)
			game->player.rotation_speed = STD_ROTATION_SPEED_3;
		else
			game->player.rotation_speed = STD_ROTATION_SPEED_4;
		game->menu.mouse_speed = game->menu.menu_index - 3;
		game->menu.menu_index = MOUSE_SPEED;
	}
	game->menu.is_selected = false;
}

int	set_resolution(t_game *game)
{
	t_resolution	new_resolution;

	new_resolution = game->menu.menu_index % 7;
	if (new_resolution == game->menu.resolution)
		return (EXIT_FAILURE);
	game->menu.resolution = new_resolution;
	if (game->menu.resolution == LIT)
	{
		game->window_width = STD_WINDOW_WIDTH_3;
		game->window_height = STD_WINDOW_HEIGHT_3;
	}
	else if (game->menu.resolution == MID)
	{
		game->window_width = STD_WINDOW_WIDTH_2;
		game->window_height = STD_WINDOW_HEIGHT_2;
	}
	else if (game->menu.resolution == BIG)
	{
		game->window_width = STD_WINDOW_WIDTH_1;
		game->window_height = STD_WINDOW_HEIGHT_1;
	}
	else
		mlx_get_screen_size(game->mlx, &game->window_width, \
			&game->window_height);
	return (EXIT_SUCCESS);
}
