/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/01 21:25:08 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_sprite_properties(t_game *game, int id);
static void	get_sprite_dimension(t_game *game, int id);
static int	get_color_offset_y(t_game *game, int y, t_sprites *sprite);
static void	draw_3d_sprite(t_game *game, t_sprites *sprite, int x, int y);

void	draw_visible_sprites(t_game *game)
{
	int		i;

	i = 0;
	game->enemy_spotted = 0;
	qsort_recursive(game->visible_sprites, 0, game->visible_sprites_num - 1);
	while (i < game->visible_sprites_num)
	{
		get_sprite_dimension(game, i);
		get_sprite_properties(game, i);
		if (game->visible_sprites->is_enemy)
		{
			if (is_enemy_spotted(game, i) && game->player.is_shooting)
				kill_enemy(game, i);
		}
		draw_3d_sprite(\
			game, \
			game->visible_sprites + i, \
			game->texture_prop.offset_x, \
			game->texture_prop.offset_y \
		);
		i++;
	}
}

static void	draw_3d_sprite(t_game *game, t_sprites *sprite, int x, int y)
{
	int		texture_y;
	int		texture_x;
	float	texel_width;

	texel_width = TILE_SIZE / game->wall_prop.proj_height;
	while (x < game->texture_prop.width)
	{
		texture_x = (x - game->texture_prop.offset_x) * texel_width;
		y = game->texture_prop.offset_y;
		if (x > 0 && x < game->window_width && \
			game->rays[x].coord.hipo > sprite->coord.hipo)
		{
			while (y < game->texture_prop.height)
			{
				if (y > 0 && y < game->window_height)
				{
					texture_y = get_color_offset_y(game, y, sprite);
					draw_pixel(game->img, \
						x, y, get_color(sprite->img, texture_x, texture_y));
				}
				y++;
			}
		}
		x++;
	}
}

static int	get_color_offset_y(t_game *game, int y, t_sprites *sprite)
{
	int		dist_from_top;

	dist_from_top = y + (game->wall_prop.proj_height / 2) - game->half_height;
	return (dist_from_top * \
		(sprite->img->height / game->wall_prop.proj_height));
}

static void	get_sprite_dimension(t_game *game, int id)
{
	game->wall_prop.proj_wall_dist = (game->half_width) \
		/ tan(FOV_ANGLE / 2);
	game->wall_prop.proj_height = \
		(TILE_SIZE / game->visible_sprites[id].coord.hipo) * \
		game->wall_prop.proj_wall_dist;
}

static void	get_sprite_properties(t_game *game, int id)
{
	float	sprite_angle;

	sprite_angle = atan2(\
				game->visible_sprites[id].coord.y - game->player.coord.y, \
				game->visible_sprites[id].coord.x - game->player.coord.x) - \
				game->player.coord.angle;
	game->texture_prop.offset_y = (game->half_height) - \
		((int)game->wall_prop.proj_height / 2);
	if (game->texture_prop.offset_y < 0)
		game->texture_prop.offset_y = 0;
	game->texture_prop.offset_x = \
		(tan(sprite_angle) * game->wall_prop.proj_wall_dist) + \
		game->half_width - (game->wall_prop.proj_height / 2);
	game->texture_prop.width = game->texture_prop.offset_x + \
		game->wall_prop.proj_height;
	game->texture_prop.height = (game->half_height) + \
		((int)game->wall_prop.proj_height / 2);
	if (game->texture_prop.height > game->window_height)
		game->texture_prop.height = game->window_height;
}
