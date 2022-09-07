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
static void	draw_radar_objects(t_game *game);

void	draw_radar(t_game *game)
{
	draw_radar_environment(game);
	draw_radar_player(game);
	draw_radar_field_of_view(game);
	draw_radar_objects(game);
	draw_small_radar(game);
}

static void	draw_radar_objects(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->sprites_num)
	{
		if (game->sprites[i].is_visible)
			game->texture_prop.color = 0xcd00cd;
		else
			game->texture_prop.color = 0xc6e2ff;
		game->texture_prop.offset_x = (game->sprites[i].coord.x - 12) * \
			MINIMAP_SCALE_FACTOR;
		game->texture_prop.offset_y = (game->sprites[i].coord.y - 12) * \
			MINIMAP_SCALE_FACTOR;
		game->texture_prop.width = 24 * MINIMAP_SCALE_FACTOR;
		game->texture_prop.height = 24 * MINIMAP_SCALE_FACTOR;
		draw_rectangle(game->minimap.radars, &game->texture_prop);
		i++;
	}
}

static void	draw_radar_field_of_view(t_game *game)
{
	int		i;

	i = 0;
	game->texture_prop.color = RED;
	game->texture_prop.offset_x = game->player.coord.x * \
		MINIMAP_SCALE_FACTOR;
	game->texture_prop.offset_y = game->player.coord.y * \
		MINIMAP_SCALE_FACTOR;
	while (i < game->ray_nums)
	{
		game->texture_prop.width = game->rays[i].coord.x * \
			MINIMAP_SCALE_FACTOR;
		game->texture_prop.height = game->rays[i].coord.y * \
			MINIMAP_SCALE_FACTOR;
		draw_line(game->minimap.radars, &game->texture_prop);
		i++;
	}
}

static void	draw_radar_environment(t_game *game)
{
	int	x;
	int	y;

	game->texture_prop.height = MINIMAP_TILE_SIZE;
	game->texture_prop.width = MINIMAP_TILE_SIZE;
	y = 0;
	while (y < game->minimap.height)
	{
		x = 0;
		game->texture_prop.offset_y = y * MINIMAP_TILE_SIZE;
		while (game->params.map[y][x])
		{
			game->texture_prop.offset_x = x * MINIMAP_TILE_SIZE;
			game->texture_prop.color = WHITE;
			if (game->params.map[y][x] == '1')
				game->texture_prop.color = BLACK;
			else if (game->params.map[y][x] == 'D')
				game->texture_prop.color = DARK_ORANGE;
			else if (game->params.map[y][x] == ' ')
				game->texture_prop.color = MIDNIGHT_BLUE;
			draw_rectangle(game->minimap.radars, &game->texture_prop);
			x++;
		}
		y++;
	}
}

static void	draw_radar_player(t_game *game)
{
	game->texture_prop.color = RED;
	game->texture_prop.offset_x = (game->player.coord.x - 16) * \
		MINIMAP_SCALE_FACTOR;
	game->texture_prop.offset_y = (game->player.coord.y - 16) * \
		MINIMAP_SCALE_FACTOR;
	game->texture_prop.width = 32 * MINIMAP_SCALE_FACTOR;
	game->texture_prop.height = 32 * MINIMAP_SCALE_FACTOR;
	draw_rectangle(game->minimap.radars, &game->texture_prop);
}
