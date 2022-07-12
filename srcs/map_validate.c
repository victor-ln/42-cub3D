/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:53:07 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/12 19:20:10 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_validation
{
	int		behind;
	int		limit;
	int		index;
}	t_validation;

static int	is_surrounded(char **map, int direction, t_validation v);
static int	validate_horizontal_max_min(char **map, int direction);
static void	empty_lines_validate(t_game *game);

void	map_validate(t_game *game)
{
	size_t		total_lines;
	size_t		line;

	empty_lines_validate(game);
	total_lines = ft_count_vectors((void **)game->params.map);
	line = 0;
	if (validate_horizontal_max_min(game->params.map, 0))
		error("Not surrounded by walls", game);
	if (validate_horizontal_max_min(game->params.map + 1, -1))
		error("Not surrounded by walls", game);
	if (validate_horizontal_max_min(game->params.map + total_lines - 2, 1))
		error("Not surrounded by walls", game);
	if (validate_horizontal_max_min(game->params.map + total_lines - 1, 0))
		error("Not surrounded by walls", game);
	while (++line < total_lines - 2)
		if (validate_horizontal_max_min(game->params.map + line, 0))
			error("Not surrounded by walls", game);
}

static int	validate_horizontal_max_min(char **map, int direction)
{
	t_validation	v;

	v.index = 0;
	v.behind = 0;
	v.limit = ft_strlen(map[direction]);
	while (map[0][v.index])
	{
		if (!ft_strchr("0NEWS", map[0][v.index]))
		{
			if (map[0][v.index] != '1' && v.behind)
				return (EXIT_FAILURE);
			v.behind = 0;
		}
		else
		{
			if (!is_surrounded(map, direction, v))
				return (EXIT_FAILURE);
			v.behind = 1;
		}
		v.index++;
	}
	return (EXIT_SUCCESS);
}

static int	is_surrounded(char **map, int direction, t_validation v)
{
	return (!((v.index + 1 > v.limit) || \
			(map[0][v.index - 1] != '1' && !v.behind) || \
			(map[direction][v.index - 1] != '1' && direction) || \
			(map[direction][v.index + 1] != '1' && direction) || \
			(map[direction][v.index] != '1' && direction)));
}

static void	empty_lines_validate(t_game *game)
{
	int	i;
	int	bl;
	int	lines_qtd;

	i = -1;
	bl = 0;
	lines_qtd = ft_count_vectors((void **)game->params.map);
	while (game->map_cub[++i])
	{
		if (game->map_cub[i] == '\n')
		{
			bl++;
			if (game->map_cub[i + 1] == '\n' && bl < lines_qtd)
				error("Invalid empty line on map", game);
		}
	}
}
