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
static void	colors_validate(t_game *game, e_environment env);
static void	empty_lines_validate(t_game *game);
static void	map_validate(t_game *game);

void	file_validate(t_game *game)
{
	//texture_validate; 2nd moment of development
	colors_validate(game, floor);
	colors_validate(game, celling);
	map_validate(game);
}

static void	colors_validate(t_game *game, e_environment env)
{
	int		i;
	int		j;
	int		color;

	if (ft_count_vectors(game->params.rgb[env] != 3))
		error("Invalid number of arguments of color identifier", game);
	i = -1;
	while (game->params.rgb[env][++i])
	{
		j = -1;
		while (game->params.rgb[env][i][++j])
			if (!ft_isspace(game->params.rgb[env][i][j]) || \
				!ft_isdigit(game->params.rgb[env][i][j]))
				error("Invalid identifier element", game);
		color = ft_atoi(color[i++]);
		if (color < 0 || color > 255)
			error("Invalid RGB scale", game);
		game->environment[env] |= color;
		game->environment[env] <<= 8;
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
				error("Invalid character on map", game);
			if (ft_strchr("NSEW ", game->params.map[i][j]))
				player++;
			if (player > 1)
				error("Invalid number of players", game);
			j++;
		}
		i++;
	}
	if (player == 0)
		error("There is no player to play", game);
}

static void	map_validate(t_game *game)
{
	int		i;
	int		j;
	int		wall[2];
	// int		inside;

	i = 0;
	characteres_and_player_nums_validate(game);
	empty_lines_validate(game);
	if (ft_count_vectors(game->params.map) < 3)
		error("Not enought number of lines", game);
	while (game->params.map[i])
	{
		j = 0;
		if (ft_strlen(game->params.map[i]) < 3)
			error("Not enought number of columns", game);
		while (ft_isspace(game->params.map[i][j]))
			j++;
		if (game->params.map[i][j] != '1')
			error("Not surrounded by walls", game);
	}
}

static void	empty_lines_validate(t_game *game)
{
	int	i;
	int	bl;
	int	lines_qtd;

	i = -1;
	bl = 0;
	lines_qtd = ft_count_vectors(game->params.map);
	while (game->map_cub[++i])
	{
		if (game->map_cub[i] == '\n')
		{
			bl++;
			if (game->cub[i + 1] == '\n' && bl <= lines_qtd)
				error("Invalid empty line on map", game);
		}
	}
}
