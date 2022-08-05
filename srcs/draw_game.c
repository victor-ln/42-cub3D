/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:21:14 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:21:14 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_ground_and_celling(t_game *game);
static int	display_game(t_game *game);
static void	draw_game(t_game *game);

void	start_game(t_game *game)
{
	display_game(game);
	mlx_hook(game->window, 2, 1, key_press, game);
	mlx_hook(game->window, 3, 1 << 1, key_release, game);
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_expose_hook(game->window, reload_image, game);
	mlx_loop_hook(game->mlx, display_game, game);
	mlx_loop(game->mlx);
}

static int	display_game(t_game *game)
{
	draw_game(game);
	mlx_do_sync(game->mlx);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	if (game->minimap.minimap_size == NORMAL)
	{
		mlx_put_image_to_window(game->mlx, game->window, \
			game->minimap.radar, 0, 0);
	}
	else
		mlx_put_image_to_window(game->mlx, game->window, \
			game->minimap.small_radar, 0, 0);
	return (0);
}

static void	draw_game(t_game *game)
{
	cast_all_rays(game);
	draw_radar(game);
	draw_ground_and_celling(game);
	draw_3d_walls(game);
}

static void	draw_ground_and_celling(t_game *game)
{
	game->img_prop->color = game->params.environment[celling];
	game->img_prop->offset_x = 0;
	game->img_prop->offset_y = 0;
	game->img_prop->height = game->window_height / 2;
	game->img_prop->width = game->window_width;
	draw_rectangle(game->img, game->img_prop);
	game->img_prop->color = game->params.environment[ground];
	game->img_prop->offset_x = 0;
	game->img_prop->offset_y = game->window_height / 2;
	game->img_prop->height = game->window_height / 2;
	game->img_prop->width = game->window_width;
	draw_rectangle(game->img, game->img_prop);
}
