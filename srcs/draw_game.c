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

// void	start_time(unsigned long *last_fps)
// {
// 	static struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	*last_fps = 0;
// }

void	start_game(t_game *game)
{
	// start_time(&game->last_fps);
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

// void	count_fps(t_game *game)
// {
// 	static struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	if ((tv.tv_usec - game->last_fps) / 1000 > 1000)
// 	{
// 		game->last_fps = tv.tv_usec;
// 		if (game->fps_string)
// 			free(game->fps_string);
// 		game->fps_string = ft_itoa(game->fps);
// 		printf("%s\n", game->fps_string);
// 		game->fps = 0; //reseta o contador de FPS
// 	}
// 	game->fps++;
// }

static int	display_game(t_game *game)
{
	// count_fps(game);
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
	if (game->fps_string)
		mlx_string_put(game->mlx, game->window, game->window_width * 0.8, 20, WHITE, game->fps_string);
	return (0);
}
