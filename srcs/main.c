/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/19 22:55:45 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_game(t_game *game);
static void	start_game(t_game *game);
static void	display_game(t_game *g);

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	init_game(game);
	load_file(game, argc, argv[argc - 1]);
	save_params(game);
	file_validate(game);
	load_environment(game);
	start_game(game);
	end_program(game);
	return (0);
}

static void	init_game(t_game *game)
{
	if (!game)
		error("Malloc Failed", game);
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->params, sizeof(t_params));
	game->params.textures = ft_calloc(sizeof(char *), 4);
	if (!game->params.textures)
		error("Malloc Failed", game);
}

static void	start_game(t_game *game)
{
	display_game(game);
	mlx_hook(game->window, 17, 0L, close_window, game);
	mlx_expose_hook(game->window, reload_image, game);
	// mlx_key_hook(game->window, key_press, game);
	// mlx_loop_hook(game->mlx, animation, game);
	mlx_loop(game->mlx);
}

static void	display_game(t_game *g)
{
	// draw_game(g);
	mlx_do_sync(g->mlx);
	mlx_put_image_to_window(g->mlx, g->window, g->img, 0, 0);
}
