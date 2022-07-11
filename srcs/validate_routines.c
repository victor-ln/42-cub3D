/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_routines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:18:18 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/06 17:43:019 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	characteres_and_player_nums_validate(t_game *game);
static void	colors_validate(t_game *game, int env);
// static void	empty_lines_validate(t_game *game);

void	file_validate(t_game *game)
{
	//texture_validate; 2nd moment of development
	colors_validate(game, ground);
	colors_validate(game, celling);
	characteres_and_player_nums_validate(game);
	map_validate(game);
}

static void	colors_validate(t_game *game, int env)
{
	int		i;
	int		j;
	int		color;

	if (ft_count_vectors((void **)game->params.rgb[env]) != 3)
		print_and_exit("Invalid number of arguments of color identifier", game);
	i = -1;
	while (game->params.rgb[env][++i])
	{
		j = -1;
		while (game->params.rgb[env][i][++j])
			if (!ft_isspace(game->params.rgb[env][i][j]) || \
				!ft_isdigit(game->params.rgb[env][i][j]))
				print_and_exit("Invalid identifier element", game);
		color = ft_atoi(game->params.rgb[env][i]);
		if (color < 0 || color > 255)
			print_and_exit("Invalid RGB scale", game);
		game->params.environment[env] |= color;
		game->params.environment[env] <<= 8;
	}
}

static void	characteres_and_player_nums_validate(t_game *game)
{
	int		i;
	int		j;
	int		player;

	i = 0;
	player = 0;
	while (game->params.map[i])
	{
		j = 0;
		while (game->params.map[i][j])
		{
			if (!ft_strchr("10NSEW ", game->params.map[i][j]))
				print_and_exit("Invalid character on map", game);
			if (ft_strchr("NSEW ", game->params.map[i][j]))
				player++;
			if (player > 1)
				print_and_exit("Invalid number of players", game);
			j++;
		}
		i++;
	}
	if (player == 0)
		print_and_exit("There is no player to play", game);
}
