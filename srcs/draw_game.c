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

static int	display_game(t_game *game);
static int	mouse_move(int x, int y, t_game *game);

void	start_game(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->window);
	display_game(game);
	mlx_hook(game->window, 2, 1, key_press, game);
	mlx_hook(game->window, 3, 2, key_release, game);
	mlx_hook(game->window, 4, 4, mouse_click, game);
	mlx_hook(game->window, 5, 8, mouse_release, game);
	mlx_hook(game->window, 6, 64, mouse_move, game);
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_expose_hook(game->window, reload_image, game);
	mlx_loop_hook(game->mlx, display_game, game);
	mlx_loop(game->mlx);
}

static int	display_game(t_game *game)
{
	cast_all_rays(game);
	get_visible_sprites(game);
	draw_radar(game);
	draw_ground_and_celling(game);
	draw_3d_walls(game);
	draw_3d_sprites(game);
	draw_crosshair(game);
	draw_weapon(game);
	mlx_do_sync(game->mlx);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, \
		game->minimap.radars[game->minimap.minimap_size], 0, 0);
	return (0);
}

static int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;

	(void)y;
	if (x != game->window_width / 2 && last_x != x)
	{
		game->player.move_direction = (x - (game->window_width / 2)) * 0.01;
		game->player.coord.angle += game->player.move_direction * \
			STD_ROTATION_SPEED_M;
		game->player.move_direction = 0;
		last_x = x;
	}
	return (0);
}
