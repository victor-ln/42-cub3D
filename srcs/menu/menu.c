/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:21:09 by afaustin          #+#    #+#             */
/*   Updated: 2022/09/03 19:34:47 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	apply_changes(t_game *game);
static int	set_resolution(t_game *game);
static void	reload_game(t_game *game);


int	key_press_menu(int key_code, t_game *game)
{
	if (key_code == ESC)
	{
		if (game->menu_screen == SELECTION_MENU)
		{
			game->is_on_the_game = true;
		}
		else
		{
			game->frame = 0;
			game->menu_index = 0;
			game->menu_screen = SELECTION_MENU;
		}
	}
	else if (key_code == ARROW_DOWN)
	{
		if (game->menu_index >= EXIT)
			game->menu_index = RESUME;
		else
			game->menu_index++;
	}
	else if (key_code == ARROW_UP)
	{
		if (game->menu_index <= RESUME)
			game->menu_index = EXIT;
		else
			game->menu_index--;
	}
	else if (key_code == ARROW_LEFT && game->is_selected)
	{
		if (game->menu_index == MOUSE_SPEED_SELECTED_1)
			game->menu_index = MOUSE_SPEED_SELECTED_3;
		else if (game->menu_index == RESOLUTION_SELECTED_1)
			game->menu_index = RESOLUTION_SELECTED_3;
		else
			game->menu_index--;
	}
	else if (key_code == ARROW_RIGHT && game->is_selected)
	{
		if (game->menu_index == MOUSE_SPEED_SELECTED_3)
			game->menu_index = MOUSE_SPEED_SELECTED_1;
		else if (game->menu_index == RESOLUTION_SELECTED_3)
			game->menu_index = RESOLUTION_SELECTED_1;
		else
			game->menu_index++;
	}
	else if ((key_code == ENTER_1 || key_code == ENTER_2))
	{
		if (game->menu_screen == OPTIONS_MENU)
		{
			if (game->menu_index == MAIN_MENU)
			{
				game->frame = 0;
				game->menu_index = 0;
				game->menu_screen = SELECTION_MENU;
			}
			else if ((game->menu_index == MOUSE_SPEED || game->menu_index == RESOLUTION))
			{
				game->menu_index = (game->menu_index * 3) + 3;
				game->is_selected = true;
			}
			else
			{
				game->is_selected = false;
				apply_changes(game);
			}
		}
		else
		{
			if (game->menu_index == EXIT)
				end_game(game);
			else if (game->menu_index == RESUME)
			{
				game->frame = 0;
				game->is_on_the_game = true;
			}
			else
			{
				game->frame = 0;
				game->menu_index = 0;
				game->menu_screen = OPTIONS_MENU;
			}
		}
	}
	else if (key_code == SHIFT)
		end_game(game);
	return (0);
}


static void	apply_changes(t_game *game)
{
	float	new_rotation_speed;

	if (game->menu_index >= RESOLUTION_SELECTED_1)
		reload_game(game);
	else
	{
		if (game->menu_index == MOUSE_SPEED_SELECTED_1)
			new_rotation_speed = STD_ROTATION_SPEED_1;
		else if (game->menu_index == MOUSE_SPEED_SELECTED_2)
			new_rotation_speed = STD_ROTATION_SPEED_2;
		else
			new_rotation_speed = STD_ROTATION_SPEED_3;
		if (game->player.rotation_speed != new_rotation_speed)
			game->player.rotation_speed = new_rotation_speed;
	}
}

static int	set_resolution(t_game *game)
{
	if (game->menu_index == RESOLUTION_SELECTED_1 && game->resolution == LIT)
		return (EXIT_FAILURE);
	if (game->menu_index == RESOLUTION_SELECTED_2 && game->resolution == MID)
		return (EXIT_FAILURE);
	if (game->menu_index == RESOLUTION_SELECTED_3 && game->resolution == BIG)
		return (EXIT_FAILURE);
	game->resolution = game->menu_index % 3;
	return (EXIT_SUCCESS);
}

static void	reload_game(t_game *game)
{
	if (set_resolution(game) == EXIT_FAILURE)
		return ;
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_image(game->mlx, game->img);
	destroy_sprites(game->minimap.radars, game->mlx, 2);
	destroy_sprites(game->options_menu, game->mlx, 16);
	destroy_sprites(game->selection_menu, game->mlx, 10);
	load_window(game);
	load_images(game);
	load_menus(game);
}
