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
	if (!game->mlx)
		error(game, "Mlx init failed", strerror(errno));
	game->screen = mlx_new_window(game->mlx, game->window_width * TILE_SIZE, \
		game->window_height * TILE_SIZE, "so_long");
	if (!game->screen)
		error(game, "Could not open a window", strerror(errno));
	game->img = mlx_new_image(game->mlx, game->window_width * TILE_SIZE, \
		game->window_height * TILE_SIZE);
	if (!game->img)
		error(game, "Could not create images", strerror(errno));
	// sprites_malloc(game);
	// if (load_sprites(&game->sprites, game->mlx))
	// 	error(game, "Could not load all sprites", 0);
	game.rays = malloc(sizeof(t_ray) * (FOV_ANGLE * game.window_width));
}
