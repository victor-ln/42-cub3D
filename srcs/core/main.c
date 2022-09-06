/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/09/05 21:36:09 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_game(t_game *game);

int	main(int argc, char **argv)
{
	t_game	game;

	init_game(&game);
	load_file(&game, argc, argv[argc - 1]);
	save_params(&game);
	file_validate(&game);
	while (1)
	{
		load_game(&game);
		start_game(&game);
	}
	return (0);
}

static void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->params, sizeof(t_params));
	ft_bzero(&game->player, sizeof(t_player));
	game->window_width = STD_WINDOW_WIDTH_1;
	game->window_height = STD_WINDOW_HEIGHT_1;
	game->resolution = BIG;
	game->mouse_speed = MEDIUM;
	game->half_width = game->window_width / 2;
	game->half_height = game->window_height / 2;
	game->params.textures = ft_calloc(sizeof(char *), 4);
	if (!game->params.textures)
		error("Malloc Failed", game);
	game->is_on_the_game = true;
}
