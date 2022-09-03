/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:39:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/03 17:05:55 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_weapon_frame(t_player *player);

void	draw_weapon(t_game *game)
{
	int		from_x;
	int		from_y;
	t_img	*weapon;

	weapon = game->weapons[game->player.weapon][game->player.weapon_frame];
	from_x = (game->half_width) - (weapon->width >> 1);
	from_y = game->window_height - weapon->height;
	draw_sprite(game->img, \
		weapon, \
		from_x, \
		from_y \
	);
	if (game->frame & 1)
		update_weapon_frame(&game->player);
}

static void	update_weapon_frame(t_player *player)
{
	if (player->is_shooting && player->weapon_frame < WEAPONS_FRAMES - 1)
	{
		player->weapon_frame++;
		if (player->weapon != knife && player->weapon != pistol)
			player->has_shooted = true;
	}
	else if (player->weapon != knife && player->weapon != pistol)
	{
		player->weapon_frame = 1;
		player->has_shooted = true;
	}
	else
	{
		player->weapon_frame = 0;
		player->is_shooting = false;
		player->has_shooted = true;
	}
}

void	draw_crosshair(t_game *game)
{
	int		from_x;
	int		from_y;

	from_x = game->half_width - \
			game->crosshair[game->enemy_spotted]->width / 2;
	from_y = game->half_height - \
			game->crosshair[game->enemy_spotted]->height / 2;
	draw_sprite(game->img, \
		game->crosshair[game->enemy_spotted], \
		from_x, \
		from_y \
	);
}

void	draw_ground_and_celling(t_game *game)
{
	game->texture_prop.color = game->params.environment[celling];
	game->texture_prop.offset_x = 0;
	game->texture_prop.offset_y = 0;
	game->texture_prop.height = game->half_height;
	game->texture_prop.width = game->window_width;
	draw_rectangle(game->img, &game->texture_prop);
	game->texture_prop.color = game->params.environment[ground];
	game->texture_prop.offset_x = 0;
	game->texture_prop.offset_y = game->half_height;
	game->texture_prop.height = game->half_height;
	game->texture_prop.width = game->window_width;
	draw_rectangle(game->img, &game->texture_prop);
}
