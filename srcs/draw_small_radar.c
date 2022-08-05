/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_radar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:51:21 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/04 20:51:51 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
static void	draw_small_radar(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	offset_x;
	int	offset_y;
	int	player_line;
	int	player_column;
	int	limit_x;
	int	limit_y;

	i = 0;
	player_line = (int)floor(game->player.coords.y / TILE_SIZE);
	player_column = (int)floor(game->player.coords.x / TILE_SIZE);
	if (player_line < 11)
		offset_y = floor(game->player.coords.y * MINIMAP_SCALE_FACTOR) - (player_line * 8);
	else if (player_line > game->minimap.height - 11)
		offset_y = floor(game->player.coords.y * MINIMAP_SCALE_FACTOR) - (game->minimap.height - player_line * 8);
	else
		offset_y = floor(game->player.coords.y * MINIMAP_SCALE_FACTOR) - 90;
	if (player_column < 20)
		offset_x = floor(game->player.coords.x * MINIMAP_SCALE_FACTOR) - (player_column * 8);
	else if (player_column > (int)game->minimap.width - 20)
		offset_x = floor(game->player.coords.x * MINIMAP_SCALE_FACTOR) - \
			((game->minimap.width - player_column) * 8);
	else
		offset_x = floor(game->player.coords.x * MINIMAP_SCALE_FACTOR) - 160;
	if (game->minimap.width > 40)
		limit_x = 40;
	else
		limit_x = game->minimap.width;
	if (game->minimap.height > 22)
		limit_y = 22;
	else
		limit_y = game->minimap.height;
	while (i < limit_y)
	{
		j = 0;
		while (j < limit_x)
		{
			y = 0;
			while (y < 8)
			{
				x = 0;
				while (x < 8)
				{
					draw_pixel(game->minimap.small_radar, \
						x + (j * game->minimap.tile_size), \
						y + (i * game->minimap.tile_size), \
						get_color(game->minimap.radar, \
							offset_x + x + (j * game->minimap.tile_size),
							offset_y + y + (i * game->minimap.tile_size)
						)
					);
					x++;
				}
				y++;
			}
			draw_pixel(game->minimap.small_radar, \
				j * game->minimap.tile_size, \
				i * game->minimap.tile_size, \
				get_color(game->minimap.radar, \
					x + (j * MINIMAP_SCALE_FACTOR * TILE_SIZE), \
					y + (i * MINIMAP_SCALE_FACTOR * TILE_SIZE)
				)
			);
			j++;
		}
		i++;
	}
}
*/
