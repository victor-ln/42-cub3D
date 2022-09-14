/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_content_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:40:05 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/13 22:38:11 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	cast_door(t_game *game, t_ray *ray, t_rays_properties *ray_prop);
static void	cast_horizontal_door(t_ray *ray, t_rays_properties *ray_prop, \
	int *closer_hit, int *further_hit);
static void	cast_vertical_door(t_ray *ray, t_rays_properties *ray_prop, \
	int *closer_hit, int *further_hit);
static void	recalculate_distance(t_game *game, t_ray *ray, \
	t_rays_properties *ray_prop);

void	get_ray_content(t_game *game, t_ray *ray)
{
	int	x;
	int	y;

	if (ray->was_hit_vertical)
	{
		x = (int)floor((ray->coord.x - ray->is_ray_facing_left) / TILE_SIZE);
		y = (int)floor(ray->coord.y / TILE_SIZE);
		x += manipulate_ray_axis(game, x, y, horizontal);
	}
	else
	{
		x = (int)floor(ray->coord.x / TILE_SIZE);
		y = (int)floor((ray->coord.y - ray->is_ray_facing_up) / TILE_SIZE);
		y += manipulate_ray_axis(game, x, y, vertical);
	}
	ray->content_type = game->params.map[y][x];
	if (ray->content_type == 'D')
		cast_door(game, ray, game->ray_prop);
}

static void	cast_door(t_game *game, t_ray *ray, t_rays_properties *ray_prop)
{
	int		closer;
	int		closer_hit[2];
	int		further_hit[2];

	closer = ray->was_hit_vertical;
	closer_hit[x] = round(ray_prop[closer].x_intercept / TILE_SIZE);
	closer_hit[y] = round(ray_prop[closer].y_intercept / TILE_SIZE);
	further_hit[x] = round(ray_prop[!closer].x_intercept / TILE_SIZE);
	further_hit[y] = round(ray_prop[!closer].y_intercept / TILE_SIZE);
	if (closer == horizontal)
		cast_horizontal_door(ray, ray_prop, closer_hit, further_hit);
	else
		cast_vertical_door(ray, ray_prop, closer_hit, further_hit);
	recalculate_distance(game, ray, ray_prop);
}

static void	cast_horizontal_door(t_ray *ray, t_rays_properties *ray_prop, \
	int *closer_hit, int *further_hit)
{
	int		closer;

	closer = ray->was_hit_vertical;
	if ((closer_hit[x] == further_hit[x] || \
		closer_hit[x] == further_hit[x] - (!ray->is_ray_facing_left) || \
		closer_hit[x] == further_hit[x] + ray->is_ray_facing_left) && \
		closer_hit[y] == further_hit[y] && \
		remainder(further_hit[y], TILE_SIZE) <= (TILE_SIZE / 2))
	{
		ray->was_hit_vertical = true;
		ray->content_type = 'O';
	}
	else
	{
		ray_prop[closer].x_intercept += ray_prop[closer].x_step / 2.0f;
		ray_prop[closer].y_intercept += ray_prop[closer].y_step / 2.0f;
		ray->content_type = 'D';
	}
}

static void	cast_vertical_door(t_ray *ray, t_rays_properties *ray_prop, \
	int *closer_hit, int *further_hit)
{
	int		closer;

	closer = ray->was_hit_vertical;
	if (closer_hit[x] == further_hit[x] && \
		(closer_hit[y] == further_hit[y] - (!ray->is_ray_facing_up) || \
		closer_hit[y] == further_hit[y] + (ray->is_ray_facing_up) || \
		closer_hit[y] == further_hit[y]) && \
		remainder(ray_prop[!closer].x_intercept, TILE_SIZE) <= (TILE_SIZE / 2))
	{
		ray->was_hit_vertical = false;
		ray->content_type = 'O';
	}
	else
	{
		ray_prop[closer].x_intercept += ray_prop[closer].x_step / 2.0f;
		ray_prop[closer].y_intercept += ray_prop[closer].y_step / 2.0f;
		ray->content_type = 'D';
	}
}

static void	recalculate_distance(t_game *game, t_ray *ray, \
	t_rays_properties *ray_prop)
{
	ray->coord.x = ray_prop[ray->was_hit_vertical].x_intercept;
	ray->coord.y = ray_prop[ray->was_hit_vertical].y_intercept;
	ray_prop[ray->was_hit_vertical].hipo = calculate_hipo(\
		(ray_prop[ray->was_hit_vertical].x_intercept - game->player.coord.x), \
		(ray_prop[ray->was_hit_vertical].y_intercept - game->player.coord.y));
	ray->coord.hipo = ray_prop[ray->was_hit_vertical].hipo;
}
