/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:08:35 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/05 19:08:23 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	manipulate_ray_axis(t_game *game, int x, int y, int axis);

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

void	cast_door(t_game *game, t_ray *ray, t_rays_properties *ray_prop)
{
	int	closer;

	closer = ray->was_hit_vertical;
	if (closer == horizontal)
	{
		if ((round(ray_prop[closer].x_intercept / TILE_SIZE) == round(ray_prop[!closer].x_intercept / TILE_SIZE) || \
			round(ray_prop[closer].x_intercept / TILE_SIZE) == round(ray_prop[!closer].x_intercept / TILE_SIZE) - (!ray->is_ray_facing_left) || \
			round(ray_prop[closer].x_intercept / TILE_SIZE) == round(ray_prop[!closer].x_intercept / TILE_SIZE)) + ray->is_ray_facing_left && \
			round(ray_prop[closer].y_intercept / TILE_SIZE) == round(ray_prop[!closer].y_intercept / TILE_SIZE) && \
			remainder(ray_prop[!closer].y_intercept, TILE_SIZE) <= TILE_SIZE / 2)
		{
			closer = vertical;
			ray->content_type = 'O';
		}
		else
		{
			ray_prop[closer].x_intercept += ray_prop[closer].x_step / 2.0f;
			ray_prop[closer].y_intercept += ray_prop[closer].y_step / 2.0f;
			ray->content_type = 'D';
		}
	}
	else
	{
		if (round(ray_prop[closer].x_intercept / TILE_SIZE) == round(ray_prop[!closer].x_intercept / TILE_SIZE) && \
			(round(ray_prop[closer].y_intercept / TILE_SIZE) == (round(ray_prop[!closer].y_intercept / TILE_SIZE)) - (!ray->is_ray_facing_up) || \
			round(ray_prop[closer].y_intercept / TILE_SIZE) == (round(ray_prop[!closer].y_intercept / TILE_SIZE)) + (ray->is_ray_facing_up) || \
			round(ray_prop[closer].y_intercept / TILE_SIZE) == (round(ray_prop[!closer].y_intercept / TILE_SIZE))) && \
			remainder(ray_prop[!closer].x_intercept, TILE_SIZE) <= (TILE_SIZE / 2))
		{
			closer = horizontal;
			ray->content_type = 'O';
		}
		else
		{
			ray_prop[closer].x_intercept += ray_prop[closer].x_step / 2.0f;
			ray_prop[closer].y_intercept += ray_prop[closer].y_step / 2.0f;
			ray->content_type = 'D';
		}
	}
	ray->coord.x = ray_prop[closer].x_intercept;
	ray->coord.y = ray_prop[closer].y_intercept;
	ray_prop[closer].hipo = calculate_hipo(\
		(ray_prop[closer].x_intercept - game->player.coord.x), \
		(ray_prop[closer].y_intercept - game->player.coord.y));
	ray->coord.hipo = ray_prop[closer].hipo;
	ray->was_hit_vertical = closer;
}

void	get_ray_content(t_game *game, int ray_id)
{
	int	x;
	int	y;

	if (game->rays[ray_id].was_hit_vertical)
	{
		x = (int)floor((game->rays[ray_id].coord.x - \
			game->rays[ray_id].is_ray_facing_left) / TILE_SIZE);
		y = (int)floor(game->rays[ray_id].coord.y / TILE_SIZE);
		x += manipulate_ray_axis(game, x, y, horizontal);
	}
	else
	{
		x = (int)floor(game->rays[ray_id].coord.x / TILE_SIZE);
		y = (int)floor((game->rays[ray_id].coord.y - \
			game->rays[ray_id].is_ray_facing_up) / TILE_SIZE);
		y += manipulate_ray_axis(game, x, y, vertical);
	}
	game->rays[ray_id].content_type = game->params.map[y][x];
	if (game->rays[ray_id].content_type == 'D')
		cast_door(game, game->rays + ray_id, game->ray_prop);
}

static int	manipulate_ray_axis(t_game *game, int x, int y, int axis)
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
