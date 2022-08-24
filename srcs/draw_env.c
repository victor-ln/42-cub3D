/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:39:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/24 18:38:43 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_weapon(t_game *game)
{
	int		from_x;
	int		from_y;

	from_x = (game->window_width / 2) - \
		game->weapons[game->player.weapon][game->player.weapon_frame]->width / 2;
	from_y = (game->window_height) - \
		game->weapons[game->player.weapon][game->player.weapon_frame]->height;
	draw_sprite(game->img, \
		game->weapons[game->player.weapon][game->player.weapon_frame], \
		from_x, \
		from_y \
	);
	if (game->player.is_shooting && game->player.weapon_frame < WEAPONS_FRAMES - 1)
	{
		game->player.weapon_frame++;
		if (game->player.weapon != knife && game->player.weapon != pistol)
			game->player.has_shooted = true;
	}
	else if (game->player.weapon != knife && game->player.weapon != pistol)
	{
		game->player.weapon_frame = 1;
		game->player.has_shooted = true;
	}
	else
	{
		game->player.weapon_frame = 0;
		game->player.is_shooting = false;
		game->player.has_shooted = true;
	}
}


void	draw_crosshair(t_game *game)
{
	int		from_x;
	int		from_y;
	int		enemy_spotted;

	enemy_spotted = 0;
	from_x = (game->window_width / 2) - \
			game->crosshair[enemy_spotted]->width / 2;
	from_y = (game->window_height / 2) - \
			game->crosshair[enemy_spotted]->height / 2;
	draw_sprite(game->img, \
		game->crosshair[enemy_spotted], \
		from_x, \
		from_y \
	);
}

void	draw_ground_and_celling(t_game *game)
{
	game->texture_prop->color = game->params.environment[celling];
	game->texture_prop->offset_x = 0;
	game->texture_prop->offset_y = 0;
	game->texture_prop->height = game->window_height / 2;
	game->texture_prop->width = game->window_width;
	draw_rectangle(game->img, game->texture_prop);
	game->texture_prop->color = game->params.environment[ground];
	game->texture_prop->offset_x = 0;
	game->texture_prop->offset_y = game->window_height / 2;
	game->texture_prop->height = game->window_height / 2;
	game->texture_prop->width = game->window_width;
	draw_rectangle(game->img, game->texture_prop);
}
