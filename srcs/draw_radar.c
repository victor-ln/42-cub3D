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

static void	draw_field_of_view(t_game *game);
static void	draw_environment(t_game *game);
static void	draw_player(t_game *game);

void	draw_radar(t_game *game)
{
	draw_environment(game);
	draw_player(game);
	draw_field_of_view(game);
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

static void	draw_field_of_view(t_game *game)
{
	int		i;

	i = 0;
	game->img_prop->color = RED;
	game->img_prop->offset_x = game->player.coord.x * \
		MINIMAP_SCALE_FACTOR;
	game->img_prop->offset_y = game->player.coord.y * \
		MINIMAP_SCALE_FACTOR;
	while (i < game->ray_nums)
	{
		game->img_prop->width = game->rays[i].coord.x * \
			MINIMAP_SCALE_FACTOR;
		game->img_prop->height = game->rays[i].coord.y * \
			MINIMAP_SCALE_FACTOR;
		draw_line(game->minimap.radar, game->img_prop);
		i++;
	}
}

static void	draw_environment(t_game *game)
{
	int	x;
	int	y;

	game->img_prop->height = game->minimap.tile_size;
	game->img_prop->width = game->minimap.tile_size;
	y = 0;
	while (y < game->minimap.height)
	{
		x = 0;
		game->img_prop->offset_y = y * game->minimap.tile_size;
		while (game->params.map[y][x])
		{
			game->img_prop->offset_x = x * game->minimap.tile_size;
			game->img_prop->color = BLACK;
			if (game->params.map[y][x] == '0')
			{
				game->img_prop->color = WHITE;
				draw_rectangle(game->minimap.radar, game->img_prop);
			}
			else
				draw_rectangle(game->minimap.radar, game->img_prop);
			x++;
		}
		y++;
	}
}

static void	draw_player(t_game *game)
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
				game->minimap.radar, \
				(game->player.coord.x + x) * MINIMAP_SCALE_FACTOR, \
				(game->player.coord.y + y) * MINIMAP_SCALE_FACTOR, \
				RED \
			);
			x++;
		}
		y++;
	}
}
