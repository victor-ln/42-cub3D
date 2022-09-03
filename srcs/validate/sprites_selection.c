/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:52:23 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/02 16:39:41 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_enemy_sprite(t_game *game, int i);
static float	get_sprite_angle(t_game *game, int sprite_id);

void	get_visible_sprites(t_game *game)
{
	int		i;
	float	sprite_angle;

	i = 0;
	game->visible_sprites_num = 0;
	while (i < game->sprites_num)
	{
		sprite_angle = get_sprite_angle(game, i);
		if (sprite_angle < (FOV_ANGLE / 2) + EPSILON)
		{
			game->sprites[i].coord.angle = sprite_angle;
			game->sprites[i].coord.hipo = calculate_hipo(\
				game->player.coord.x - game->sprites[i].coord.x, \
				game->player.coord.y - game->sprites[i].coord.y \
			);
			if (game->sprites[i].is_enemy)
				update_enemy_sprite(game, i);
			game->visible_sprites[game->visible_sprites_num++] = \
				game->sprites[i];
		}
		i++;
	}
}

static void	update_enemy_sprite(t_game *game, int i)
{
	if (game->enemies[i].is_dead)
	{
		if (!game->enemies[i].enemy_frame)
			game->enemies[i].enemy_frame = dying_guard_01;
		if (game->enemies[i].enemy_frame <= dying_guard_05)
			game->sprites[i].img = game->enemy[game->enemies[i].enemy_frame++];
	}
	else if (game->sprites[i].coord.hipo < 400)
	{
		if (game->enemies[i].enemy_frame > shooting_guard_02 || \
			game->enemies[i].enemy_frame < shooting_guard_01)
			game->enemies[i].enemy_frame = shooting_guard_01;
		game->sprites[i].img = game->enemy[game->enemies[i].enemy_frame++];
	}
	else
		game->sprites[i].img = game->enemy[front_idle_guard];
}

static float	get_sprite_angle(t_game *game, int sprite_id)
{
	float	sprite_angle;

	sprite_angle = game->player.coord.angle - \
		atan2(game->sprites[sprite_id].coord.y - game->player.coord.y, \
			game->sprites[sprite_id].coord.x - game->player.coord.x);
	if (sprite_angle > M_PI)
		sprite_angle -= (M_PI + M_PI);
	if (sprite_angle < -M_PI)
		sprite_angle += (M_PI + M_PI);
	return (fabs(sprite_angle));
}
