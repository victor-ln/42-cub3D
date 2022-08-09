/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_radar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:51:21 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/08 21:28:49 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_small_radar(t_game *game)
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
	player_line = (int)floor(game->player.coord.y / TILE_SIZE);
	player_column = (int)floor(game->player.coord.x / TILE_SIZE);
	// printf("Player Line %d Player Column %d\n", player_line, player_column);
	if (player_line < 5)
		offset_y = 0;
	else if (player_line > game->minimap.height - 5)
		offset_y = (11 - (game->minimap.height - player_line)) * game->minimap.tile_size;
	else
		offset_y = floor(game->player.coord.y * MINIMAP_SCALE_FACTOR) - 90;
	if (player_column < 10)
		offset_x = 0;
	else if (player_column > (int)game->minimap.width - 10)
		offset_x = (20 - (game->minimap.width - player_column)) * game->minimap.tile_size;
	else
		offset_x = floor(game->player.coord.x * MINIMAP_SCALE_FACTOR) - 160;
	if (game->minimap.width > 20)
		limit_x = 20;
	else
		limit_x = game->minimap.width;
	if (game->minimap.height > 11)
		limit_y = 11;
	else
		limit_y = game->minimap.height;
	while (i < limit_y)
	{
		j = 0;
		while (j < limit_x)
		{
			y = 0;
			while (y < 16)
			{
				x = 0;
				while (x < 16)
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
