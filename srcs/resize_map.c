/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 22:02:27 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/06 22:02:419 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

typedef struct s_validation
{
	size_t	last_line;
	size_t	line;
	size_t	counter;
}	t_validation;

void	print_matrix(char **map);

static int	is_garbage(char **map, t_validation v);
static int	just_walls_and_spaces(char *map_line);
static void	shift_back_matrix(char **ptr);

void	resize_line(t_game *game)
{
	int		line;
	int		counter;

	line = 0;
	counter = 0;
	while (just_walls_and_spaces(game->params.map[line]))
		line++;
	while (counter < line - 1)
	{
		shift_back_matrix(game->params.map);
		counter++;
	}
	line = ft_count_vectors((void **)game->params.map) - 1;
	counter = line;
	while (just_walls_and_spaces(game->params.map[line]))
		line--;
	while (counter > line + 1)
		shift_back_matrix(game->params.map + counter--);
}

/*
	Testar função.
*/
void	resize_column(t_game *game)
{
	t_validation	v;
	char			*temp;

	v.line = -1;
	v.last_line = ft_count_vectors((void **)game->params.map) - 1;
	while (game->params.map[++v.line])
	{
		v.counter = ft_strlen(game->params.map[v.line]) - 1;
		while (is_garbage(game->params.map, v))
			v.counter--;
		if (v.counter == ft_strlen(game->params.map[v.line]) - 1)
			continue ;
		temp = ft_substr(game->params.map[v.line], 0, v.counter);
		ft_free_null(game->params.map[v.line]);
		game->params.map[v.line] = temp;
	}
}

static int	is_garbage(char **map, t_validation v)
{
	if (map[v.line][v.counter - 1] == '0')
		return (0);
	if (v.line && (v.counter <= (ft_strlen(map[v.line - 1] - 1))))
		if (map[v.line - 1][v.counter] == '0' || \
			map[v.line - 1][v.counter - 1] == '0')
			return (0);
	if (v.line < v.last_line && (v.counter <= (ft_strlen(map[v.line + 1] - 1))))
		if (map[v.line + 1][v.counter] == '0' || \
			map[v.line + 1][v.counter - 1] == '0')
			return (0);
	return (1);
}

static int	just_walls_and_spaces(char *map_line)
{
	int		i;

	i = 0;
	while (map_line[i])
		if (ft_strchr("0NEWS", map_line[i++]))
			return (0);
	return (1);
}

static void	shift_back_matrix(char **ptr)
{
	int	i;

	i = 0;
	free(ptr[i]);
	while (ptr[i])
	{
		ptr[i] = ptr[i + 1];
		i++;
	}
}
