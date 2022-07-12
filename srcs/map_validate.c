/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:53:07 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/11 21:40:51 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	validate_horizontal_max_min(char **map, char c, int dir, int index);
static void	empty_lines_validate(t_game *game);

void	map_validate(t_game *game)
{
	size_t	total_lines;
	size_t		line;

	empty_lines_validate(game);
	total_lines = ft_count_vectors((void **)game->params.map);
	line = 0;
	if (validate_horizontal_max_min(game->params.map, '0', 0, 0))
		print_and_exit("Not surrounded by walls 1", game);
	if (validate_horizontal_max_min(game->params.map + 1, '0', -1, 0))
		print_and_exit("Not surrounded by walls 2", game);
	if (validate_horizontal_max_min(game->params.map + total_lines - 1, '0', 1, 0))
		print_and_exit("Not surrounded by walls 3", game);
	if (validate_horizontal_max_min(game->params.map + total_lines, '0',0, 0))
		print_and_exit("Not surrounded by walls 4", game);
	while (++line < total_lines - 1)
		if (validate_horizontal_max_min(game->params.map + line, '0', 0, 0))
			print_and_exit("Not surrounded by walls 5", game);
}

static int	validate_horizontal_max_min(char **map, char c, int dir, int index)
{
	int		behind;
	int		limit;

	behind = 0;
	limit = ft_strlen(map[dir]);
	printf("%s\n", map[dir]);
	while (map[0][index])
	{
		if (index == 24 && dir)
			index = 24;
		if (map[0][index] != c)
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
			if (game->map_cub[i + 1] == '\n' && bl <= lines_qtd)
				print_and_exit("Invalid empty line on map", game);
		}
	}
}
