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

void	start_time(t_fps *fps)
{
	fps->fps_length = 1000 / FPS_RATE;
	fps->ticks_last_frame = 0;
	fps->delta = 0;
	fps->frames = 0;
	fps->fps_string = 0;
}

void	start_game(t_game *game)
{
	start_time(&game->fps);
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

void	count_fps(t_game *game)
{
	while (clock() < (game->fps.ticks_last_frame + game->fps.fps_length))
		continue ;
	game->fps.delta = (clock() - game->fps.ticks_last_frame) / 1000.0f; 
	game->fps.ticks_last_frame = clock();
	if (game->fps.delta > 0)
		game->fps.frames = (CLOCKS_PER_SEC / game->fps.delta) / 1000;
	free(game->fps.fps_string);
	game->fps.fps_string = ft_itoa(game->fps.frames);
}

static int	display_game(t_game *game)
{
	count_fps(game);
	move_player(game);
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
	mlx_string_put(game->mlx, game->window, game->window_width * 0.8, 20, WHITE, game->fps.fps_string);
	return (0);
}
