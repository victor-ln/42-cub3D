/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_selection_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:52:23 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/10/04 21:28:05 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void		update_enemy_sprite(t_game *game, int i);
static float	get_sprite_angle(t_game *game, int sprite_id);
static void		get_closest_sprites(t_game *game);

void	get_visible_sprites(t_game *game)
{
	int		i;
	float	sprite_angle;

	i = -1;
	game->visible_sprites_num = 0;
	get_closest_sprites(game);
	while (++i < game->sprites_num)
	{
		game->sprites[i].is_visible = false;
		sprite_angle = get_sprite_angle(game, i);
		if (sprite_angle < (FOV_ANGLE / 2) + EPSILON)
		{
			game->sprites[i].coord.angle = sprite_angle;
			game->sprites[i].coord.hipo = calculate_hipo(\
				game->player.coord.x - game->sprites[i].coord.x, \
				game->player.coord.y - game->sprites[i].coord.y \
			);
			game->visible_sprites[game->visible_sprites_num++] = \
				game->sprites[i];
			game->sprites[i].is_visible = true;
		}
		if (game->sprites[i].is_enemy)
			update_enemy_sprite(game, i);
	}
	ft_bzero(game->visible_sprites, game->sprites_num);
	qsort_recursive(game->visible_sprites, 0, game->visible_sprites_num - 1);
}

static void	update_enemy_sprite(t_game *game, int i)
{
	if (game->frame & 1)
		return ;
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
	if (sprite_angle > PI)
		sprite_angle -= TWO_PI;
	if (sprite_angle < -PI)
		sprite_angle += TWO_PI;
	return (fabs(sprite_angle));
}

static void	get_closest_sprites(t_game *game)
{
	int	i;

	i = -1;
	game->closest_sprites_num = 0;
	while (++i < game->sprites_num)
	{
		if (game->sprites[i].coord.hipo <= TILE_SIZE)
		{
			if (game->sprites[i].is_enemy)
				if (game->enemies[game->sprites[i].enemy_index].is_dead)
					continue ;
			game->closest_sprites[game->closest_sprites_num] = i;
			game->closest_sprites_num++;
		}
	}
}
