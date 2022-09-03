/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:23:50 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/03 18:10:32 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	save_rotation_angle(t_game *game, char c);

void	load_player(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	game->player.weapon = pistol;
	game->player.rotation_speed = STD_ROTATION_SPEED_2;
	game->player.movement_speed = 8;
	while (game->params.map[i])
	{
		j = 0;
		while (game->params.map[i][j])
		{
			if (ft_strchr("NSWE", game->params.map[i][j]))
			{
				save_rotation_angle(game, game->params.map[i][j]);
				game->player.coord.x = j * TILE_SIZE + (TILE_SIZE * 0.5);
				game->player.coord.y = i * TILE_SIZE + (TILE_SIZE * 0.5);
				game->params.map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	save_rotation_angle(t_game *game, char c)
{
	if (c == 'N')
		game->player.coord.angle = M_PI + M_PI_2;
	else if (c == 'S')
		game->player.coord.angle = M_PI_2;
	else if (c == 'W')
		game->player.coord.angle = M_PI;
	else if (c == 'E')
		game->player.coord.angle = 0;
}

void	load_rays(t_game *game)
{
	game->ray_nums = game->window_width / RAY_STRIP;
	game->rays = malloc(sizeof(t_ray) * game->ray_nums);
	if (!game->rays)
		error("Malloc Failed", game);
}

size_t	get_max_line_size(char **map)
{
	size_t	max_line_size;
	int		i;

	max_line_size = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_line_size)
			max_line_size = ft_strlen(map[i]);
		i++;
	}
	return (max_line_size);
}
