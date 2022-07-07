/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/06 17:20:12 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		error("Malloc Failed", game);
	game->file_content = load_file(argc, argv[argc - 1]);
	save_params(game);
	file_validate(game);
	return (0);
}
