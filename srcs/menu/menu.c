/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:21:09 by afaustin          #+#    #+#             */
/*   Updated: 2022/09/06 22:07:02 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	esc_pressed(t_game *game);
static void	enter_pressed(t_game *game);
static void	increase_menu_index(t_menu *menu, int last_index);
static void	decrease_menu_index(t_menu *menu, int first_index);

#define FIND_FST_INDEX	-1
#define FIND_LST_INDEX	-2

int	key_press_menu(int keycode, t_game *game)
{
	game->frame = 0;
	if (keycode == ESC)
		esc_pressed(game);
	else if (keycode == ARROW_DOWN && !game->menu.is_selected)
		increase_menu_index(&game->menu, EXIT);
	else if (keycode == ARROW_UP && !game->menu.is_selected)
		decrease_menu_index(&game->menu, RESUME);
	else if (keycode == ARROW_RIGHT && game->menu.is_selected)
		increase_menu_index(&game->menu, FIND_LST_INDEX);
	else if (keycode == ARROW_LEFT && game->menu.is_selected)
		decrease_menu_index(&game->menu, FIND_FST_INDEX);
	else if (keycode == ENTER_1 || keycode == ENTER_2)
		enter_pressed(game);
	return (0);
}

static void	esc_pressed(t_game *game)
{
	if (game->menu.menu_screen == SELECTION_MENU)
		game->is_on_the_game = true;
	else if (game->menu.is_selected)
	{
		game->menu.menu_index /= 7;
		game->menu.is_selected = false;
	}
	else
		change_menu(&game->menu, SELECTION_MENU);
}

static void	increase_menu_index(t_menu *menu, int last_index)
{
	int		first_index;

	first_index = 2;
	if (last_index == FIND_LST_INDEX)
	{
		if (menu->menu_index < RESOLUTION_SELECTED_1)
			last_index = MOUSE_SPEED_SELECTED_4;
		else
			last_index = RESOLUTION_SELECTED_4;
		first_index = 3;
	}
	if (menu->menu_index >= last_index)
		menu->menu_index = last_index - first_index;
	else
		menu->menu_index++;
}

static void	decrease_menu_index(t_menu *menu, int first_index)
{
	int		last_index;

	last_index = 2;
	if (first_index == FIND_FST_INDEX)
	{
		if (menu->menu_index > MOUSE_SPEED_SELECTED_4)
			first_index = RESOLUTION_SELECTED_1;
		else
			first_index = MOUSE_SPEED_SELECTED_1;
		last_index = 3;
	}
	if (menu->menu_index <= first_index)
		menu->menu_index = first_index + last_index;
	else
		menu->menu_index--;
}

static void	enter_pressed(t_game *game)
{
	if (game->menu.menu_screen == OPTIONS_MENU)
	{
		if (game->menu.is_selected)
			apply_changes(game);
		else if (game->menu.menu_index == MAIN_MENU)
			change_menu(&game->menu, SELECTION_MENU);
		else
		{
			game->menu.is_selected = true;
			game->menu.menu_index = (game->menu.menu_index * 4) + 3;
			if (game->menu.menu_index == MOUSE_SPEED_SELECTED_1)
				game->menu.menu_index += game->menu.mouse_speed;
			else
				game->menu.menu_index += game->menu.resolution;
		}
	}
	else if (game->menu.menu_index == EXIT)
		end_game(game);
	else if (game->menu.menu_index == RESUME)
		game->is_on_the_game = true;
	else
		change_menu(&game->menu, OPTIONS_MENU);
}
