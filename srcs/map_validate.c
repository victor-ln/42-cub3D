/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:53:07 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/12 18:42:44 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	validate_horizontal_max_min(char **map, int dir);
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

static int	validate_horizontal_max_min(char **map, int dir)
{
	int		behind;
	int		limit;
	int		index;

	index = 0;
	behind = 0;
	limit = ft_strlen(map[dir]);
	while (map[0][index])
	{
		if (!ft_strchr("0NEWS", map[0][index]))
		{
			if (map[0][index] != '1' && behind)
				return (EXIT_FAILURE);
			behind = 0;
		}
		else
		{
			if ((index + 1 > limit) || \
				(map[0][index - 1] != '1' && !behind) || \
				(map[dir][index - 1] != '1' && dir) || \
				(map[dir][index + 1] != '1' && dir) || \
				(map[dir][index] != '1' && dir))
				return (EXIT_FAILURE);
			behind = 1;
		}
		index++;
	}
	return (EXIT_SUCCESS);
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
