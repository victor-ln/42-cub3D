/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:08:35 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/08 18:31:10 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
}

double	calculate_hipo(double x, double y)
{
	return (sqrt(x * x + y * y));
}

void	ray_constructor(t_game *game, int ray_id)
{
	normalize_angle(&game->rays[ray_id].coord.angle);
	if (game->rays[ray_id].coord.angle > 0 && \
		game->rays[ray_id].coord.angle < PI)
		game->rays[ray_id].is_ray_facing_up = false;
	else
		game->rays[ray_id].is_ray_facing_up = true;
	if (game->rays[ray_id].coord.angle > PI_PLUS_HALF_PI || \
		game->rays[ray_id].coord.angle < HALF_PI)
		game->rays[ray_id].is_ray_facing_left = false;
	else
		game->rays[ray_id].is_ray_facing_left = true;
}

int	manipulate_ray_axis(t_game *game, int x, int y, int axis)
{
	if (axis == horizontal)
	{
		if (x < (int)ft_strlen(game->params.map[y]) - 1 && \
			game->params.map[y][x + 1] == 'O')
			return (1);
		else if (x > 0 && game->params.map[y][x - 1] == 'O')
			return (-1);
	}
	else if (axis == vertical)
	{
		if (y < game->minimap.height - 1 && \
			x < (int)ft_strlen(game->params.map[y + 1]) && \
			game->params.map[y + 1][x] == 'O')
			return (1);
		else if (y > 0 && x < (int)ft_strlen(game->params.map[y - 1]) && \
			game->params.map[y - 1][x] == 'O')
			return (-1);
	}
	return (0);
}
