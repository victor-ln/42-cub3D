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

static void	cast_ray(t_game *game, int ray_id);
static void	cast_vertical(t_game *game, t_rays_properties *vert, t_ray *ray);
static void	cast_horizontal(t_game *game, t_rays_properties *horz, t_ray *ray);
static void	calculate_distances(t_game *game, int ray_id);

void	cast_all_rays(t_game *game)
{
	int		i;
	float	angle;

	i = 0;
	angle = game->player.coord.angle - (FOV_ANGLE / 2);
	while (i < game->ray_nums)
	{
		game->rays[i].coord.angle = angle;
		ray_constructor(game, i);
		cast_ray(game, i);
		get_ray_content(game, i);
		angle += FOV_ANGLE / game->ray_nums;
		i++;
	}
}

static void	cast_ray(t_game *game, int ray_id)
{
	game->ray_prop[vertical].was_hit = false;
	game->ray_prop[horizontal].was_hit = false;
	game->ray_prop[vertical].hipo = __FLT_MAX__;
	game->ray_prop[horizontal].hipo = __FLT_MAX__;
	cast_vertical(game, game->ray_prop + vertical, game->rays + ray_id);
	cast_horizontal(game, game->ray_prop + horizontal, game->rays + ray_id);
	calculate_distances(game, ray_id);
}

static void	cast_vertical(t_game *game, t_rays_properties *vert, t_ray *ray)
{
	vert->x_intercept = floor(game->player.coord.x / TILE_SIZE) * TILE_SIZE;
	vert->x_intercept += ray->is_ray_facing_right * TILE_SIZE;
	vert->y_intercept = game->player.coord.y + \
		(vert->x_intercept - game->player.coord.x) * tan(ray->coord.angle);
	vert->x_step = TILE_SIZE;
	if (ray->is_ray_facing_left == true)
		vert->x_step *= -1;
	vert->y_step = TILE_SIZE * tan(ray->coord.angle);
	if (vert->y_step < 0 && ray->is_ray_facing_down == true)
		vert->y_step *= -1;
	if (vert->y_step > 0 && ray->is_ray_facing_up == true)
		vert->y_step *= -1;
	while (vert->x_intercept >= 0 && vert->x_intercept < game->minimap.widthpx
		&& vert->y_intercept >= 0 && vert->y_intercept < game->minimap.heightpx)
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
	horz->y_intercept += ray->is_ray_facing_down * TILE_SIZE;
	horz->x_intercept = game->player.coord.x + \
		(horz->y_intercept - game->player.coord.y) / tan(ray->coord.angle);
	horz->y_step = TILE_SIZE;
	if (ray->is_ray_facing_up == true)
		horz->y_step *= -1;
	horz->x_step = TILE_SIZE / tan(ray->coord.angle);
	if (horz->x_step < 0 && ray->is_ray_facing_right)
		horz->x_step *= -1;
	if (horz->x_step > 0 && ray->is_ray_facing_left)
		horz->x_step *= -1;
	while (horz->x_intercept >= 0 && horz->x_intercept < game->minimap.widthpx
		&& horz->y_intercept >= 0 && horz->y_intercept < game->minimap.heightpx)
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

static void	calculate_distances(t_game *game, int ray_id)
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
	game->rays[ray_id].coord.x = game->ray_prop[closer].x_intercept;
	game->rays[ray_id].coord.y = game->ray_prop[closer].y_intercept;
	game->rays[ray_id].coord.hipo = game->ray_prop[closer].hipo;
	game->rays[ray_id].was_hit_vertical = closer;
}
