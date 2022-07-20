/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:24:00 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:24:00 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_environment(t_game *game)
{
	game->mlx = mlx_init();
	game->window_width = TILE_SIZE * 10;
	game->window_height = TILE_SIZE * 5;
	if (!game->mlx)
		error("Mlx init failed", game);
	game->window = mlx_new_window(game->mlx, game->window_width, \
		game->window_height, "cub3D");
	if (!game->window)
		error("Could not open a window", game);
	game->img = mlx_new_image(game->mlx, game->window_width, \
		game->window_height);
	if (!game->img)
		error("Could not create images", game);
	// sprites_malloc(game);
	// if (load_sprites(&game->sprites, game->mlx))
	// 	error("Could not load all sprites", game);
	// game->rays = malloc(sizeof(t_ray) * (FOV_ANGLE * game->window_width));
}
