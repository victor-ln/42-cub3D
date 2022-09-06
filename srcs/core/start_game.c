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

static int	game_loop(t_game *game);
static void	display_game(t_game *game);
static void	display_general_menu(t_game *game);
static void	display_options_menu(t_game *game);

void	start_game(t_game *game)
{
	start_time(game);
	mlx_hook(game->window, 2, 1, key_press_game, game);
	mlx_hook(game->window, 3, 2, key_release, game);
	mlx_hook(game->window, 4, 4, mouse_click, game);
	mlx_hook(game->window, 5, 8, mouse_release, game);
	mlx_hook(game->window, 6, 64, mouse_move, game);
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	destroy_game(game);
	free_game(game);
}

static int	game_loop(t_game *game)
{
	if (game->is_on_the_game)
		display_game(game);
	else if (game->menu_screen == SELECTION_MENU)
		display_general_menu(game);
	else
		display_options_menu(game);
	return (0);
}

static void	display_game(t_game *game)
{
	if (++game->frame == 2)
		game->frame = 0;
	count_fps(game);
	move_player(game);
	cast_all_rays(game);
	get_visible_sprites(game);
	draw_radar(game);
	draw_ground_and_celling(game);
	draw_3d_walls(game);
	draw_visible_sprites(game);
	draw_crosshair(game);
	draw_weapon(game);
	mlx_do_sync(game->mlx);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, \
		game->minimap.radars[game->minimap.minimap_size], 0, 0);
	mlx_string_put(game->mlx, game->window, \
		game->fps.fps_offset_x, game->fps.fps_offset_y, \
		WHITE, game->fps.fps_string);
}

static void	display_general_menu(t_game *game)
{
	int			frame;
	static int	direction = 1;

	count_fps(game);
	game->frame += direction;
	if (game->frame >= 8)
	{
		direction = -1;
		game->frame--;
	}
	else if (game->frame <= 0)
		direction = 1;
	if (game->frame < 2)
		frame = 0;
	else
		frame = (game->frame / 2) + (game->menu_index * 3);
	mlx_put_image_to_window(game->mlx, game->window, \
		game->selection_menu[frame], 0, 0);
}

static void	display_options_menu(t_game *game)
{
	int			frame;
	static int	direction = 1;

	count_fps(game);
	if (game->menu_index < MOUSE_SPEED_SELECTED_1)
	{
		game->frame += direction;
		if (game->frame >= 8)
		{
			direction = -1;
			game->frame--;
		}
		else if (game->frame <= 0)
			direction = 1;
		if (game->frame < 2)
			frame = 0;
		else
			frame = (game->frame / 2) + (game->menu_index * 3);
	}
	else
		frame = game->menu_index + 7;
	mlx_put_image_to_window(game->mlx, game->window, \
		game->options_menu[frame], 0, 0);
}
