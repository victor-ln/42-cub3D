/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_radar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:40:03 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/01 21:06:22 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_radar_field_of_view(t_game *game);
static void	draw_radar_environment(t_game *game);
static void	draw_radar_player(t_game *game);

void	draw_radar(t_game *game)
{
	draw_radar_environment(game);
	draw_radar_player(game);
	draw_radar_field_of_view(game);
	draw_radar_objects(game);
	if (game->minimap.minimap_size == BIG)
		draw_small_radar(game);
}

void	draw_sprite(t_img *image, t_img *sprite, int x, int y)
{
	register int	i;
	register int	j;

	j = 0;
	while (j < sprite->height)
	{
		i = 0;
		while (i < sprite->width)
		{
			draw_pixel(image, x + i, y + j, get_color(sprite, i, j));
			i++;
		}
		j++;
	}
}

static void	draw_radar_field_of_view(t_game *game)
{
	int		i;

	i = 0;
	game->texture_prop->color = RED;
	game->texture_prop->offset_x = game->player.coord.x * \
		MINIMAP_SCALE_FACTOR;
	game->texture_prop->offset_y = game->player.coord.y * \
		MINIMAP_SCALE_FACTOR;
	while (i < game->ray_nums)
	{
		game->texture_prop->width = game->rays[i].coord.x * \
			MINIMAP_SCALE_FACTOR;
		game->texture_prop->height = game->rays[i].coord.y * \
			MINIMAP_SCALE_FACTOR;
		draw_line(game->minimap.radars[NORMAL], game->texture_prop);
		i++;
	}
}

static void	draw_radar_environment(t_game *game)
{
	int	x;
	int	y;

	game->texture_prop->height = game->minimap.tile_size;
	game->texture_prop->width = game->minimap.tile_size;
	y = 0;
	while (y < game->minimap.height)
	{
		x = -1;
		game->texture_prop->offset_y = y * game->minimap.tile_size;
		while (game->params.map[y][++x])
		{
			game->texture_prop->offset_x = x * game->minimap.tile_size;
			if (game->params.map[y][x] == '0')
				game->texture_prop->color = WHITE;
			else if (game->params.map[y][x] == '1')
				game->texture_prop->color = BLACK;
			else if (game->params.map[y][x] == 'D')
				game->texture_prop->color = DARK_ORANGE;
			else if (game->params.map[y][x] == ' ')
				game->texture_prop->color = MIDNIGHT_BLUE;
			else
				game->texture_prop->color = WHITE;
			draw_rectangle(game->minimap.radars[NORMAL], game->texture_prop);
		}
		y++;
	}
}

static void	draw_radar_player(t_game *game)
{
	int		y;
	int		x;

	y = -16;
	while (y < 16)
	{
		x = -16;
		while (x < 16)
		{
			draw_pixel(
				game->minimap.radars[NORMAL], \
				(game->player.coord.x + x) * MINIMAP_SCALE_FACTOR, \
				(game->player.coord.y + y) * MINIMAP_SCALE_FACTOR, \
				RED \
			);
			x++;
		}
		y++;
	}
}
