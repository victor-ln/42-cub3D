/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:08:35 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/14 16:31:58 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
