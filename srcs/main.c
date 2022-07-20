/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/19 22:20:48 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_game(t_game *game);
static void	start_game(t_game *game);

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	init_game(game);
	load_file(game, argc, argv[argc - 1]);
	save_params(game);
	file_validate(game);
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
	mlx_hook(game->screen, 17, 0L, close_window, game);
	mlx_expose_hook(game->screen, reload_image, game);
	mlx_key_hook(game->screen, key_press, game);
	// mlx_loop_hook(game->mlx, animation, game);
	mlx_loop(game->mlx);
}

void	display_game(t_game *g)
{
	if (g->kills == g->enemies_num && !g->coins_num)
		g->door = 1;
	if (++g->frame == 8)
		g->frame = 0;
	draw_game(g);
	mlx_do_sync(g->mlx);
	mlx_put_image_to_window(g->mlx, g->screen, g->img, 0, 0);
	hero_got_caught(g);
	move_enemies(g);
	mlx_string_put(g->mlx, g->screen, 10, 10, C_WHITE, "Moves :");
	mlx_string_put(g->mlx, g->screen, 60, 10, C_WHITE, g->moves_str);
	ft_delay(45500);
}
