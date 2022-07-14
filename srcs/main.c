/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/12 22:34:22 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_game(t_game *game);

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	init_game(game);
	load_file(game, argc, argv[argc - 1]);
	save_params(game);
	file_validate(game);
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
