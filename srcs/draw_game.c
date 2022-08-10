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
static void	draw_crosshair(t_game *game);
static void	mouse_move(t_game *game);

void	start_game(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->window);
	display_game(game);
	mlx_hook(game->window, 2, 1, key_press, game);
	mlx_hook(game->window, 3, 1 << 1, key_release, game);
	mlx_hook(game->window, 17, 0, close_window, game);
	// mlx_mouse_hook(game->window, mouse_click, game);
	mlx_expose_hook(game->window, reload_image, game);
	mlx_loop_hook(game->mlx, display_game, game);
	mlx_loop(game->mlx);
}

static int	display_game(t_game *game)
{
	mouse_move(game);
	cast_all_rays(game);
	draw_radar(game);
	draw_ground_and_celling(game);
	draw_3d_walls(game);
	draw_crosshair(game);
	mlx_do_sync(game->mlx);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, \
		game->minimap.radars[game->minimap.minimap_size], 0, 0);
	return (0);
}

static void	mouse_move(t_game *game)
{
	static int	last_x = -1;
	int			x;
	int			y;

	mlx_mouse_get_pos(game->mlx, game->window, &x, &y);
	if (x != game->window_width / 2 && last_x != x)
	{
		game->player.move_direction = (x - (game->window_width / 2)) * 0.01;
		game->player.coord.angle += game->player.move_direction * \
			STD_ROTATION_SPEED;
		game->player.move_direction = 0;
		last_x = x;
	}
}

static void	draw_ground_and_celling(t_game *game)
{
	game->texture_prop->color = game->params.environment[celling];
	game->texture_prop->offset_x = 0;
	game->texture_prop->offset_y = 0;
	game->texture_prop->height = game->window_height / 2;
	game->texture_prop->width = game->window_width;
	draw_rectangle(game->img, game->texture_prop);
	game->texture_prop->color = game->params.environment[ground];
	game->texture_prop->offset_x = 0;
	game->texture_prop->offset_y = game->window_height / 2;
	game->texture_prop->height = game->window_height / 2;
	game->texture_prop->width = game->window_width;
	draw_rectangle(game->img, game->texture_prop);
}

static void	draw_crosshair(t_game *game)
{
	int		from_x;
	int		from_y;
	int		enemy_spotted;

	enemy_spotted = 0;
	from_x = (game->window_width / 2) - \
			game->crosshair[enemy_spotted]->width / 2;
	from_y = (game->window_height / 2) - \
			game->crosshair[enemy_spotted]->height / 2;
	draw_sprite(game->img, \
		game->crosshair[enemy_spotted], \
		from_x, \
		from_y \
	);
}
