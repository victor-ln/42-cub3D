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
static void	draw_3d_walls(t_game *game);
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
	mlx_put_image_to_window(game->mlx, game->window, game->extended_minimap, 0, 0);
	return (0);
}

static void	draw_game(t_game *game)
{
	cast_all_rays(game);
	draw_minimap(game);
	draw_ground_and_celling(game);
	draw_3d_walls(game);
}

static void	draw_ground_and_celling(t_game *game)
{
	game->img_properties->color = BLACK;
	game->img_properties->offset_x = 0;
	game->img_properties->offset_y = 0;
	game->img_properties->height = game->window_height / 2;
	game->img_properties->width = game->window_width;
	draw_rectangle(game->img, game->img_properties);
	game->img_properties->color = WHITE;
	game->img_properties->offset_x = 0;
	game->img_properties->offset_y = game->window_height / 2;
	game->img_properties->height = game->window_height / 2;
	game->img_properties->width = game->window_width;
	draw_rectangle(game->img, game->img_properties);
}

static void	draw_3d_walls(t_game *game)
{
	int					column;
	float				projected_wall_dist;
	float				projected_wall_height;
	float				ray_distance;

	column = 0;
	while (column < game->ray_nums)
	{
		ray_distance = game->rays[column].coords.distance * 
			cos(game->rays[column].coords.angle - game->player.coords.angle);
		projected_wall_dist = ((game->window_width) / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / ray_distance) * projected_wall_dist;
		if (projected_wall_height > (unsigned)(game->window_height))
			projected_wall_height = (game->window_height);
		game->img_properties->color = RED;
		if (game->rays[column].content_type == '1')
			game->img_properties->color = RED;
		else if (game->rays[column].content_type == '2')
			game->img_properties->color = GREEN;
		else if (game->rays[column].content_type == '3')
			game->img_properties->color = BLUE;
		game->img_properties->offset_x = column * RAY_STRIP;
		game->img_properties->offset_y = (game->window_height - projected_wall_height) / 2;
		game->img_properties->width = RAY_STRIP;
		game->img_properties->height = projected_wall_height;
		draw_rectangle(game->img, game->img_properties);
		column++;
	}
}
