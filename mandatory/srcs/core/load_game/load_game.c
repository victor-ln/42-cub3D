/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:24:00 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:24:00 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_game(t_game *game)
{
	if (game->window_height < 300 || game->window_width < 300)
		error("Resolution must be rather than 300 x 300", game);
	game->mlx = mlx_init();
	if (!game->mlx)
		error("Mlx init failed", game);
	load_window(game);
	load_images(game);
	load_textures(game);
	load_player(game);
	load_rays(game);
}

void	load_window(t_game *game)
{
	game->window = mlx_new_window(game->mlx, game->window_width, \
		game->window_height, "cub3D");
	if (!game->window)
		error("Could not open a window", game);
}

void	load_images(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, game->window_width, \
		game->window_height);
	if (!game->img.img)
		error("Could not create images", game);
	game->img.img->bpp /= 8;
	game->img.img->size_line /= game->img.img->bpp;
	game->img.buffer = (uint32_t *)game->img.img->data;
}
