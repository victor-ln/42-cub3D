/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/22 22:35:23 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


// void	draw_enemies(t_game *game)
// {
	
// }

/** 
 * TODO: normalize player angle.
*/

void	get_visible_sprites(t_game *game)
{
	int		i;
	float	sprite_angle;

	i = 0;
	while (i < game->sprites_num)
	{
		sprite_angle = game->player.coord.angle - \
			atan2(game->sprites[i].coord.x, game->sprites[i].coord.y);
		if (sprite_angle < (FOV_ANGLE / 2))
		{
			game->sprites[i].is_visible = true;
			game->sprites[i].coord.angle = sprite_angle;
		}
		else
			game->sprites[i].is_visible = false;
		i++;
	}
}

void	draw_radar_objects(t_game *game)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	while (i < game->sprites_num)
	{
		if (game->sprites[i].is_visible)
			game->texture_prop->color = 0xffd700;
		else
			game->texture_prop->color = 0xc6e2ff;
		y = -16;
		while (y < 16)
		{
			x = -16;
			while (x < 16)
			{
				draw_pixel(\
					game->minimap.radars[NORMAL], \
					(game->sprites[i].coord.x + x) * MINIMAP_SCALE_FACTOR,
					(game->sprites[i].coord.y + y) * MINIMAP_SCALE_FACTOR,
					game->texture_prop->color
				);
				x++;
			}
			y++;
		}
		i++;
	}
}
