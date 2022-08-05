/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:08:35 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/04 22:10:29 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, (M_PI + M_PI));
	if (*angle < 0)
		*angle = (M_PI + M_PI) + *angle;
}

static	double	calculate_hypo(double x, double y)
{
	return (sqrt(x * x + y * y));
}

void	get_ray_content(t_game *game, int ray_id)
{
	int	x;
	int	y;

	if (game->rays[ray_id].was_hit_vertical)
	{
		x = floor((game->rays[ray_id].coord.x - \
			game->rays[ray_id].is_ray_facing_left) / TILE_SIZE);
		y = floor(game->rays[ray_id].coord.y / TILE_SIZE);
	}
	else
	{
		x = floor(game->rays[ray_id].coord.x / TILE_SIZE);
		y = floor((game->rays[ray_id].coord.y - \
			game->rays[ray_id].is_ray_facing_up) / TILE_SIZE);
	}
	game->rays[ray_id].content_type = game->params.map[y][x];
}

void	ray_constructor(t_game *game, int ray_id)
{
	game->rays[ray_id].was_hit_vertical = false;
	normalize_angle(&game->rays[ray_id].coord.angle);
	game->rays[ray_id].is_ray_facing_down = false;
	game->rays[ray_id].is_ray_facing_up = false;
	game->rays[ray_id].is_ray_facing_right = false;
	game->rays[ray_id].is_ray_facing_left = false;
	if (game->rays[ray_id].coord.angle > 0 && \
		game->rays[ray_id].coord.angle < M_PI)
		game->rays[ray_id].is_ray_facing_down = true;
	else
		game->rays[ray_id].is_ray_facing_up = true;
	if (game->rays[ray_id].coord.angle > M_PI + M_PI_2 || \
		game->rays[ray_id].coord.angle < M_PI_2)
		game->rays[ray_id].is_ray_facing_right = true;
	else
		game->rays[ray_id].is_ray_facing_left = true;
}
