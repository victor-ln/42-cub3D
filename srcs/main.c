/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/11 21:40:49 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_game(t_game *game);

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	init_game(game);
	game->file_content = load_file(argc, argv[argc - 1]);
	save_params(game);
	file_validate(game);
	return (0);
}

static void	init_game(t_game *game)
{
	if (!game)
		print_and_exit("Malloc Failed", game);
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->params, sizeof(t_params));
	game->params.textures = malloc(sizeof(char *) * 4);
	if (!game->params.textures)
		print_and_exit("Malloc Failed", game);
}
