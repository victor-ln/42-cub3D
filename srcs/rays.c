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

enum e_leveling {
	horizontal,
	vertical
};

typedef struct s_leveling
{
	int		x_intercept;
	int		y_intercept;
	int		x_step;
	int		y_step;
	double	distance;
	bool	found_hit;
}	t_leveling;

static int	get_distance_between_two_points(int	x, int y);
static void	cast_ray(t_ray *ray, t_game *game);
static void	vertical_interception(t_leveling *vertical, t_ray *ray, t_game *game);
static void	horizontal_interception(t_leveling *vertical, t_ray *ray, t_game *game);

void	cast_all_rays(t_game *game)
{
	int		column_id;
	int		ray_angle;

	column_id = 0;
	ray_angle = game->player.coords.angle - (FOV_ANGLE / 2);
	while (column_id < game->ray_nums)
	{
		game->rays[column_id].coords.angle = ray_angle;
		cast_ray(game->rays + column_id, game);
		ray_angle += FOV_ANGLE / game->ray_nums;
		column_id++;
	}
}

static void	cast_ray(t_ray *ray, t_game *game)
{
	t_leveling	leveling[2];
	int			closer;

	ray->is_facing_down = ray->coords.angle > 0 && ray->coords.angle < M_PI;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = ray->coords.angle < M_PI_2 || ray->coords.angle > M_PI + M_PI_2;
	ray->is_facing_left = !ray->is_facing_right;
	leveling[horizontal].distance = __INT_MAX__;
	leveling[vertical].distance = __INT_MAX__;
	horizontal_interception(&leveling[horizontal], ray, game);
	vertical_interception(&leveling[vertical], ray, game);
	if (leveling[horizontal].found_hit == true)
		leveling[horizontal].distance = get_distance_between_two_points
			(leveling[horizontal].x_intercept - game->player.coords.x, \
			leveling[horizontal].y_intercept - game->player.coords.y);
	if (leveling[vertical].found_hit == true)
		leveling[vertical].distance = get_distance_between_two_points
			(leveling[vertical].x_intercept - game->player.coords.x, \
			leveling[vertical].y_intercept - game->player.coords.y);
	closer = leveling[horizontal].distance > leveling[vertical].distance;
	ray->coords.angle = leveling[closer].distance;
	ray->coords.x = leveling[closer].x_intercept;
	ray->coords.y = leveling[closer].y_intercept;
	ray->was_hit_vertical = closer;
}

static int	get_distance_between_two_points(int	x, int y)
{
	return (sqrt(x * x + y * y));
}

void	horizontal_interception(t_leveling *horizontal, t_ray *ray, t_game *game)
{
	horizontal->found_hit = false;
	horizontal->y_intercept = game->player.coords.y / TILE_SIZE * TILE_SIZE;
	horizontal->y_intercept += TILE_SIZE * ray->is_facing_down;
	horizontal->x_intercept = game->player.coords.x + \
		(horizontal->y_intercept - game->player.coords.y) / tan(ray->coords.angle);
	horizontal->y_step = TILE_SIZE * \
		(ray->is_facing_up * -1 + ray->is_facing_down);
	horizontal->x_step = TILE_SIZE / tan(ray->coords.angle);
	if (horizontal->x_step > 0 && ray->is_facing_left)
		horizontal->x_step *= -1;
	if (horizontal->x_step < 0 && ray->is_facing_right)
		horizontal->x_step *= -1;
	while (horizontal->y_intercept >= 0 && horizontal->y_intercept <= game->width * TILE_SIZE && \
		horizontal->x_intercept >= 0 && horizontal->x_intercept <= game->height * TILE_SIZE)
	{
		if (!has_wall_at(game, horizontal->y_intercept, horizontal->x_intercept - ray->is_facing_up))
		{
			horizontal->found_hit = true;
			return ;
		}
		horizontal->y_intercept += horizontal->x_step;
		horizontal->x_intercept += horizontal->y_step;
	}
}

static void	vertical_interception(t_leveling *vertical, t_ray *ray, t_game *game)
{
	vertical->found_hit = false;
	vertical->x_intercept = game->player.coords.x / TILE_SIZE * TILE_SIZE;
	vertical->x_intercept += TILE_SIZE * ray->is_facing_right;
	vertical->y_intercept = game->player.coords.y + \
		(vertical->x_intercept - game->player.coords.x) * tan(ray->coords.angle);
	vertical->x_step = TILE_SIZE;
	vertical->x_step *= (ray->is_facing_left * -1) + ray->is_facing_right;
	vertical->y_step = TILE_SIZE * tan(ray->coords.angle);
	if (vertical->y_step > 0 && ray->is_facing_up)
		vertical->y_step *= -1;
	if (vertical->y_step < 0 && ray->is_facing_down)
		vertical->y_step *= -1;
	while (vertical->y_intercept >= 0 && vertical->y_intercept <= game->width * TILE_SIZE && \
		vertical->x_intercept >= 0 && vertical->x_intercept <= game->height * TILE_SIZE)
	{
		if (!has_wall_at(game, vertical->y_intercept, vertical->x_intercept - ray->is_facing_up))
		{
			vertical->found_hit = true;
			return ;
		}
		vertical->y_intercept += vertical->x_step;
		vertical->x_intercept += vertical->y_step;
	}
}
