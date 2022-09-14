/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:08:35 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/13 22:34:59 by afaustin         ###   ########.fr       */
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

void	ray_constructor(t_ray *ray)
{
	normalize_angle(&ray->coord.angle);
	if (ray->coord.angle > 0 && ray->coord.angle < PI)
		ray->is_ray_facing_up = false;
	else
		ray->is_ray_facing_up = true;
	if (ray->coord.angle > PI_PLUS_HALF_PI || ray->coord.angle < HALF_PI)
		ray->is_ray_facing_left = false;
	else
		ray->is_ray_facing_left = true;
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
