/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:21:22 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:21:22 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cast_ray(t_game *game, t_ray *ray);
static void	cast_vertical(t_game *game, t_rays_properties *vert, t_ray *ray);
static void	cast_horizontal(t_game *game, t_rays_properties *horz, t_ray *ray);
static void	calculate_distances(t_game *game, t_ray *ray);

void	cast_all_rays(t_game *game)
{
	int		i;
	float	angle;

	i = 0;
	angle = game->player.coord.angle - (FOV_ANGLE / 2);
	while (i < game->ray_nums)
	{
		game->rays[i].coord.angle = angle;
		cast_ray(game, game->rays + i);
		angle += FOV_ANGLE / game->ray_nums;
		i++;
	}
}

static void	cast_ray(t_game *game, t_ray *ray)
{
	game->ray_prop[vertical].was_hit = false;
	game->ray_prop[horizontal].was_hit = false;
	game->ray_prop[vertical].hipo = __FLT_MAX__;
	game->ray_prop[horizontal].hipo = __FLT_MAX__;
	ray_constructor(ray);
	cast_vertical(game, game->ray_prop + vertical, ray);
	cast_horizontal(game, game->ray_prop + horizontal, ray);
	calculate_distances(game, ray);
}

static void	cast_vertical(t_game *game, t_rays_properties *vert, t_ray *ray)
{
	vert->x_intercept = floor(game->player.coord.x / TILE_SIZE) * TILE_SIZE;
	vert->x_intercept += !ray->is_ray_facing_left * TILE_SIZE;
	vert->y_intercept = game->player.coord.y + \
		(vert->x_intercept - game->player.coord.x) * tan(ray->coord.angle);
	vert->x_step = TILE_SIZE;
	if (ray->is_ray_facing_left == true)
		vert->x_step *= -1;
	vert->y_step = TILE_SIZE * tan(ray->coord.angle);
	if (vert->y_step < 0 && !ray->is_ray_facing_up == true)
		vert->y_step *= -1;
	if (vert->y_step > 0 && ray->is_ray_facing_up == true)
		vert->y_step *= -1;
	while (vert->x_intercept >= 0 && vert->x_intercept < game->minimap_widthpx
		&& vert->y_intercept >= 0 && vert->y_intercept < game->minimap_heightpx)
	{
		if (has_wall_at(game, vert->x_intercept - ray->is_ray_facing_left, \
			vert->y_intercept))
		{
			vert->was_hit = true;
			break ;
		}
		vert->x_intercept += vert->x_step;
		vert->y_intercept += vert->y_step;
	}
}

static void	cast_horizontal(t_game *game, t_rays_properties *horz, t_ray *ray)
{
	horz->y_intercept = floor(game->player.coord.y / TILE_SIZE) * TILE_SIZE;
	horz->y_intercept += !ray->is_ray_facing_up * TILE_SIZE;
	horz->x_intercept = game->player.coord.x + \
		(horz->y_intercept - game->player.coord.y) / tan(ray->coord.angle);
	horz->y_step = TILE_SIZE;
	if (ray->is_ray_facing_up == true)
		horz->y_step *= -1;
	horz->x_step = TILE_SIZE / tan(ray->coord.angle);
	if (horz->x_step < 0 && !ray->is_ray_facing_left)
		horz->x_step *= -1;
	if (horz->x_step > 0 && ray->is_ray_facing_left)
		horz->x_step *= -1;
	while (horz->x_intercept >= 0 && horz->x_intercept < game->minimap_widthpx
		&& horz->y_intercept >= 0 && horz->y_intercept < game->minimap_heightpx)
	{
		if (has_wall_at(game, horz->x_intercept, horz->y_intercept - \
			ray->is_ray_facing_up))
		{
			horz->was_hit = true;
			break ;
		}
		horz->x_intercept += horz->x_step;
		horz->y_intercept += horz->y_step;
	}
}

static void	calculate_distances(t_game *game, t_ray *ray)
{
	int	closer;

	if (game->ray_prop[horizontal].was_hit == true)
		game->ray_prop[horizontal].hipo = calculate_hipo(\
			(game->ray_prop[horizontal].x_intercept - game->player.coord.x), \
			(game->ray_prop[horizontal].y_intercept - game->player.coord.y));
	if (game->ray_prop[vertical].was_hit == true)
		game->ray_prop[vertical].hipo = calculate_hipo(\
			(game->ray_prop[vertical].x_intercept - game->player.coord.x), \
			(game->ray_prop[vertical].y_intercept - game->player.coord.y));
	closer = game->ray_prop[vertical].hipo < game->ray_prop[horizontal].hipo;
	ray->coord.x = game->ray_prop[closer].x_intercept;
	ray->coord.y = game->ray_prop[closer].y_intercept;
	ray->coord.hipo = game->ray_prop[closer].hipo;
	ray->was_hit_vertical = closer;
}
