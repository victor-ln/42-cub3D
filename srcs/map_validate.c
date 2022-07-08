/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:53:07 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/07 21:44:32 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	validate_horizontal_max_min(char **map, size_t line, int dir);
static int	**get_wall_positions(char **map, size_t nbr_of_lines);
static void	validate_outside_map(t_game *game, int zeros[2], int line);
static void	validate_inside_map(t_game *game, int zeros[2], int line);
static void	empty_lines_validate(t_game *game);

void	map_validate(t_game *game)
{
	size_t	total_lines;
	int		zeros[2];
	int		**walls;
	int		line;
	int		col;

	total_lines = ft_count_vectors(game->params.map);
	walls = get_wall_positions(game->params.map, total_lines);
	line = -1;
	validate_HorizontalMaxMin(game->params.map, 0, -1);
	validate_HorizontalMaxMin(game->params.map, total_lines - 1, 1);
	while (++line < total_lines)
	{
		// validate_outside_map();
		// validate_inside_map();
	}
}

static void	validate_outside_map(t_game *game, int zeros[2], int line)
{
	zeros[0] = ft_strchr(game->params.map[line], '0');
	zeros[1] = ft_strrchr(game->params.map[line], '0');
	if (zeros[0])
		// if (validate_firstlastcolomns())
			error("Not surrounded by walls", game);
}

static void	validate_inside_map(t_game *game, int zeros[2], int line)
{
	// 
}

static int	validate_horizontal_max_min(char **map, size_t line, int dir)
{
	int		j;
	int		tile;

	while (map[line][++j])
	{
		if (map[line][j] != '0')
		{
			tile = 0;
			continue ;
		}
		if ((map[line][j - 1] != '1' || tile) && \
			map[line + dir][j - 1] != '1' && \
			map[line + dir][j] != '1')
			return (EXIT_FAILURE);
		tile = 1;
	}
	return (EXIT_SUCCESS);
}

static int	**get_wall_positions(char **map, size_t nbr_of_lines)
{
	int		**walls;
	int		line;

	line = 0;
	walls = ft_calloc(sizeof(int *), nbr_of_lines);
	if (!walls)
		return (NULL);
	while (line < nbr_of_lines)
	{
		walls[line] = ft_calloc(sizeof(int), 2);
		if (!walls[line])
		{
			ft_free_matrix(walls, line);
			return (NULL);
		}
		if (ft_strchr(map[line], '1') == NULL)
		{
			ft_free_matrix(walls, line);
			return (NULL);
		}
		walls[line][0] = ft_strchr(map[line], '1') - map[line];
		walls[line][1] = ft_strrchr(map[line], '1') - map[line];
		line++;
	}
	return (walls);
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
			if (game->map_cub[i + 1] == '\n' && bl <= lines_qtd)
				error("Invalid empty line on map", game);
		}
	}
}
