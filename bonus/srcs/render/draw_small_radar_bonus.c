/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_radar_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:51:21 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/08 19:30:22 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	get_offset(t_game *game);

void	draw_small_radar(t_game *game)
{
	int		x;
	int		y;

	get_offset(game);
	y = 0;
	while (y < game->minimap.small_radar_limit_y)
	{
		x = 0;
		while (x < game->minimap.small_radar_limit_x)
		{
			draw_pixel(game->img, x, y, get_color(\
					game->minimap.radars, \
					game->texture_prop.offset_x + x,
					game->texture_prop.offset_y + y)
				);
			x++;
		}
		y++;
	}
}

static void	get_offset(t_game *game)
{
	int	player_line;
	int	player_column;
	int	mid_x;
	int	mid_y;

	player_line = (int)floor(game->player.coord.y / TILE_SIZE);
	player_column = (int)floor(game->player.coord.x / TILE_SIZE);
	mid_x = (game->minimap.small_radar_widthpx / MINIMAP_TILE_SIZE) >> 1;
	mid_y = (game->minimap.small_radar_heightpx / MINIMAP_TILE_SIZE) >> 1;
	if (player_line <= mid_y)
		game->texture_prop.offset_y = 0;
	else if (player_line >= game->minimap.height - mid_y)
		game->texture_prop.offset_y = (game->minimap.height - \
		((mid_y << 1) + (mid_y & 1))) * MINIMAP_TILE_SIZE;
	else
		game->texture_prop.offset_y = floor(game->player.coord.y * \
			MINIMAP_SCALE_FACTOR) - (game->minimap.small_radar_heightpx >> 1);
	if (player_column <= mid_x)
		game->texture_prop.offset_x = 0;
	else if (player_column >= game->minimap.width - mid_x)
		game->texture_prop.offset_x = (game->minimap.width - \
			(mid_x << 1) + (mid_x & 1)) * MINIMAP_TILE_SIZE;
	else
		game->texture_prop.offset_x = floor(game->player.coord.x * \
			MINIMAP_SCALE_FACTOR) - (game->minimap.small_radar_widthpx >> 1);
}
