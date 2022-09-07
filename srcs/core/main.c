/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/09/06 22:06:32 by vlima-nu         ###   ########.fr       */
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
	game->menu.resolution = BIG;
	game->menu.mouse_speed = FAST;
	game->half_width = game->window_width / 2;
	game->half_height = game->window_height / 2;
	game->wall_prop.proj_wall_dist = game->half_width / tan(FOV_ANGLE / 2);
	game->params.textures = ft_calloc(sizeof(char *), 4);
	game->is_on_the_game = true;
	game->player.weapon = pistol;
	game->player.rotation_speed = STD_ROTATION_SPEED_3;
	game->player.movement_speed = 8;
	if (!game->params.textures)
		error("Malloc Failed", game);
}
