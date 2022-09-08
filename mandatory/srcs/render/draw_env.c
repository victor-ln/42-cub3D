/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:39:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 19:01:40 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ground_and_celling(t_game *game)
{
	game->texture_prop.color = game->params.environment[celling];
	game->texture_prop.offset_x = 0;
	game->texture_prop.offset_y = 0;
	game->texture_prop.height = game->half_height;
	game->texture_prop.width = game->window_width;
	draw_rectangle(game->img, &game->texture_prop);
	game->texture_prop.color = game->params.environment[ground];
	game->texture_prop.offset_x = 0;
	game->texture_prop.offset_y = game->half_height;
	game->texture_prop.height = game->half_height;
	game->texture_prop.width = game->window_width;
	draw_rectangle(game->img, &game->texture_prop);
}
