/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:53:07 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/13 23:06:08 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_validation
{
	int		behind;
	int		column_limit[2];
	int		column;
	size_t	line_num;
	size_t	total_lines;
}	t_validation;

static int	is_surrounded(char **map, t_validation v);
static int	line_validate(char **map, t_validation v);
static int	is_closed_on_the_sides(char **map);
static void	empty_lines_validate(t_game *game);

void	map_validate(t_game *game)
{
	t_validation	v;

	resize_line(game);
	resize_column(game);
	empty_lines_validate(game);
	ft_bzero(v.column_limit, sizeof(int) * 2);
	v.total_lines = ft_count_vectors((void **)game->params.map);
	v.line_num = -1;
	v.column = 0;
	v.behind = 0;
	while (++v.line_num < v.total_lines)
		if (line_validate(game->params.map, v))
			error("Not surrounded by walls", game);
}

static int	line_validate(char **map, t_validation v)
{
	if (!is_closed_on_the_sides(map + v.line_num))
		return (EXIT_FAILURE);
	if (v.line_num)
		v.column_limit[TOP_LINE] = ft_strlen(map[v.line_num - 1]) - 1;
	if (v.line_num < v.total_lines - 1)
		v.column_limit[BOT_LINE] = ft_strlen(map[v.line_num + 1]) - 1;
	while (map[v.line_num][v.column])
	{
		if (!ft_strchr("0NEWS", map[v.line_num][v.column]))
		{
			if (map[v.line_num][v.column] != '1' && v.behind)
				return (EXIT_FAILURE);
			v.behind = 0;
		}
		else
		{
			if (!is_surrounded(map, v))
				return (EXIT_FAILURE);
			v.behind = 1;
		}
		v.column++;
	}
	return (EXIT_SUCCESS);
}

static int	is_surrounded(char **map, t_validation v)
{
	if (!v.line_num || v.line_num == v.total_lines - 1)
		return (0);
	if (map[v.line_num][v.column - 1] != '1' && !v.behind)
		return (0);
	if (v.line_num)
		if ((v.column >= v.column_limit[TOP_LINE] || \
			(map[v.line_num - 1][v.column - 1] == ' ') || \
			(map[v.line_num - 1][v.column] == ' ')))
			return (0);
	if (v.line_num < v.total_lines - 1)
		if ((v.column >= v.column_limit[BOT_LINE] || \
			(map[v.line_num + 1][v.column - 1] == ' ') || \
			(map[v.line_num + 1][v.column] == ' ')))
			return (0);
	return (1);
}

static int	is_closed_on_the_sides(char **map)
{
	if (ft_strrchr(*map, '1') < ft_strrchr(*map, '0'))
		return (0);
	if (ft_strchr(*map, '1') > ft_strchr(*map, '0') && ft_strchr(*map, '0'))
		return (0);
	return (1);
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
