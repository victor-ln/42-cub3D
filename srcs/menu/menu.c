/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:21:09 by afaustin          #+#    #+#             */
/*   Updated: 2022/09/05 20:48:46 by afaustin         ###   ########.fr       */
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
			game->is_on_the_game = true;
		else if (game->is_selected)
		{
			game->menu_index /= 6;
			game->is_selected = false;
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
				if (game->menu_index == MOUSE_SPEED_SELECTED_1)
					game->menu_index += game->mouse_speed;
				else
					game->menu_index += game->resolution;
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
	// int		mouse_x;
	// int		mouse_y;

	if (game->menu_index >= RESOLUTION_SELECTED_1)
	{
		reload_game(game);
		game->menu_index = RESOLUTION;
		// mlx_mouse_show(game->mlx, game->window);
		// mlx_mouse_move(game->mlx, game->window, game->half_width, game->half_height);
		// mlx_mouse_get_pos(game->mlx, game->window, &mouse_x, &mouse_y);
	}
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
		game->mouse_speed = game->menu_index % 3;
		game->menu_index = MOUSE_SPEED;
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
	if (game->resolution == LIT)
	{
		game->window_width = STD_WINDOW_WIDTH_3;
		game->window_height = STD_WINDOW_HEIGHT_3;
	}
	else if (game->resolution == MID)
	{
		game->window_width = STD_WINDOW_WIDTH_2;
		game->window_height = STD_WINDOW_HEIGHT_2;
	}
	else
	{
		game->window_width = STD_WINDOW_WIDTH_1;
		game->window_height = STD_WINDOW_HEIGHT_1;
	}
	game->half_width = game->window_width / 2;
	game->half_height = game->window_height / 2;
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
	ft_free_null(game->rays);
	load_rays(game);
	load_window(game);
	load_images(game);
	load_menus(game);
	start_time(game);
	mlx_hook(game->window, 2, 1, key_press_game, game);
	mlx_hook(game->window, 3, 2, key_release, game);
	mlx_hook(game->window, 4, 4, mouse_click, game);
	mlx_hook(game->window, 6, 64, mouse_move, game);
	mlx_hook(game->window, 5, 8, mouse_release, game);
	mlx_hook(game->window, 17, 0, close_window, game);
}
