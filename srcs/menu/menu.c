/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:21:09 by afaustin          #+#    #+#             */
/*   Updated: 2022/09/02 21:55:58 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press_menu(int key_code, t_game *game)
{
	if (key_code == ESC)
	{
		game->is_on_the_game = true;
		game->mlx->loop_hook = display_game;
		game->window->hooks[2].hook = key_press_game;
	}
	else if (key_code == ARROW_DOWN)
	{
		if (game->menu_index == 2)
			game->menu_index = 0;
		else
			game->menu_index++;
	}
	else if (key_code == ARROW_UP)
	{
		if (!game->menu_index)
			game->menu_index = 2;
		else
			game->menu_index--;
	}
	else if (key_code == ALT)
		end_game(game);
	return (0);
}