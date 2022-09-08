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

void	start_game(t_game *game)
{
	mlx_hook(game->window, 2, 1, key_press_game, game);
	mlx_hook(game->window, 3, 2, key_release, game);
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, display_game, game);
	mlx_loop(game->mlx);
	destroy_game(game);
	free_game(game);
}

static int	display_game(t_game *game)
{
	move_player(game);
	cast_all_rays(game);
	draw_ground_and_celling(game);
	draw_3d_walls(game);
	mlx_do_sync(game->mlx);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}
