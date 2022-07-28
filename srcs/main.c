/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/27 21:59:54 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_game(t_game *game);
static void	start_game(t_game *game);
static int	display_game(t_game *g);

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	init_game(game);
	load_file(game, argc, argv[argc - 1]);
	save_params(game);
	file_validate(game);
	print_matrix(game->params.map);
	load_game(game);
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
	ft_bzero(&game->player, sizeof(t_player));
	game->params.textures = ft_calloc(sizeof(char *), 4);
	if (!game->params.textures)
		error("Malloc Failed", game);
}

static void	start_game(t_game *game)
{
	display_game(game);
	mlx_hook(game->window, 2, 1, key_press, game);
	mlx_hook(game->window, 3, 1 << 1, key_release, game);
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_expose_hook(game->window, reload_image, game);
	mlx_loop_hook(game->mlx, display_game, game);
	mlx_loop(game->mlx);
}

static int	display_game(t_game *g)
{
	draw_game(g);
	mlx_do_sync(g->mlx);
	mlx_put_image_to_window(g->mlx, g->window, g->img, 0, 0);
	return (0);
}
