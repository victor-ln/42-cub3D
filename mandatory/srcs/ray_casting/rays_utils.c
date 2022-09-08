/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:08:35 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 19:03:26 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, (M_PI + M_PI));
	if (*angle < 0)
		*angle = (M_PI + M_PI) + *angle;
}

double	calculate_hipo(double x, double y)
{
	return (sqrt(x * x + y * y));
}

void	ray_constructor(t_game *game, int ray_id)
{
	normalize_angle(&game->rays[ray_id].coord.angle);
	if (game->rays[ray_id].coord.angle > 0 && \
		game->rays[ray_id].coord.angle < M_PI)
		game->rays[ray_id].is_ray_facing_up = false;
	else
		game->rays[ray_id].is_ray_facing_up = true;
	if (game->rays[ray_id].coord.angle > M_PI + M_PI_2 || \
		game->rays[ray_id].coord.angle < M_PI_2)
		game->rays[ray_id].is_ray_facing_left = false;
	else
		game->rays[ray_id].is_ray_facing_left = true;
}
