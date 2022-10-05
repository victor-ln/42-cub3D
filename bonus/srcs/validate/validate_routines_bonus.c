/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_routines_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:18:18 by afaustin          #+#    #+#             */
/*   Updated: 2022/10/04 21:02:13 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	characteres_and_player_nums_validate(t_game *game);
static void	colors_validate(t_game *game, int env);

void	file_validate(t_game *game)
{
	colors_validate(game, ground);
	colors_validate(game, celling);
	characteres_and_player_nums_validate(game);
	map_validate(game);
	doors_validate(game);
}

static void	colors_validate(t_game *game, int env)
{
	int		i;
	int		j;
	int		color;

	if (ft_count_vectors((void **)game->params.rgb[env]) != 3)
		error("Invalid number of arguments of color identifier", game);
	i = -1;
	while (game->params.rgb[env][++i])
	{
		j = -1;
		while (game->params.rgb[env][i][++j])
			if (!ft_isspace(game->params.rgb[env][i][j]) && \
				!ft_isdigit(game->params.rgb[env][i][j]))
				error("Invalid identifier element", game);
		color = ft_atoi(game->params.rgb[env][i]);
		if (color < 0 || color > 255)
			error("Invalid RGB scale", game);
		game->params.environment[env] |= color;
		if (i < 2)
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
		j = -1;
		while (game->params.map[i][++j])
		{
			if ((game->params.map[i][j] >= 88 && game->params.map[i][j] <= 126) || \
				(game->params.map[i][j] >= 35 && game->params.map[i][j] <= 43))
				continue ;
			if (!ft_strchr("10NSEWDA ", game->params.map[i][j]))
				error("Invalid character on map", game);
			if (ft_strchr("NSEW", game->params.map[i][j]))
				player++;
			if (player > 1)
				error("Invalid number of players", game);
		}
		i++;
	}
	if (player == 0)
		error("There is no player to play", game);
}
