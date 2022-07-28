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

static double	calculate_hypo(double x, double y);
static void		normalize_angle(double *angle);
static void 	cast_ray(t_game *game, int ray_id);
static void		ray_constructor(t_game *game, int ray_id);
static void		get_ray_content(t_game *game, int ray_id);

void	cast_all_rays(t_game *game)
{
	int		i;
	float	angle;

	i = 0;
	angle = game->player.coords.angle - (FOV_ANGLE / 2);
	while (i < game->ray_nums)
	{
		game->rays[i].coords.angle = angle;
		cast_ray(game, i);
		get_ray_content(game, i);
		angle += FOV_ANGLE / game->ray_nums;
		i++;
	}
}

static void get_ray_content(t_game *game, int ray_id)
{
	int	x;
	int	y;

	if (game->rays[ray_id].was_hit_vertical)
	{
		x = floor((game->rays[ray_id].coords.x - \
			game->rays[ray_id].is_ray_facing_left) / TILE_SIZE);
		y = floor(game->rays[ray_id].coords.y / TILE_SIZE);
	}
	else
	{
		x = floor(game->rays[ray_id].coords.x / TILE_SIZE);
		y = floor((game->rays[ray_id].coords.y - \
			game->rays[ray_id].is_ray_facing_up) / TILE_SIZE);
	}
	game->rays[ray_id].content_type = game->params.map[y][x];
}

static void	cast_ray(t_game *game, int ray_id)
{
	float	x_interception;
	float	y_interception;
	float	x_step;
	float	y_step;
	float	horizontalX;
	float	horizontalY;
	float	angle;
	bool	horizontal_was_hit;
	float	horizontal_distance;
	float	verticalX;
	float	verticalY;
	bool	vertical_was_hit;
	float	vertical_distance;


	vertical_was_hit = false;
	horizontal_was_hit = false;
	vertical_distance = __INT_MAX__;
	horizontal_distance = __INT_MAX__;
	ray_constructor(game, ray_id);
	angle = game->rays[ray_id].coords.angle;
	/*HORIZONTAL INTERCEPTION*/
	y_interception = floor(game->player.coords.y / TILE_SIZE) * TILE_SIZE;
	y_interception += game->rays[ray_id].is_ray_facing_down * TILE_SIZE;
	x_interception = game->player.coords.x + (y_interception - game->player.coords.y) / tan(angle);
	y_step = TILE_SIZE;
	if (game->rays[ray_id].is_ray_facing_up == true)
		y_step *= -1;
	x_step = TILE_SIZE / tan(angle);
	if (x_step < 0 && game->rays[ray_id].is_ray_facing_right)
		x_step *= -1;
	if (x_step > 0 && game->rays[ray_id].is_ray_facing_left)
		x_step *= -1;
	while (x_interception >= 0 && x_interception < (game->width * TILE_SIZE) && 
		y_interception >= 0 && y_interception < (game->height * TILE_SIZE))
	{
		if (has_wall_at(game, x_interception, y_interception - game->rays[ray_id].is_ray_facing_up))
		{
			horizontalX = x_interception;
			horizontalY = y_interception;
			horizontal_was_hit = true;
			break;
		}
		x_interception += x_step;
		y_interception += y_step;
	}
	/*VERTICAL INTERCEPTION*/
	x_interception = floor(game->player.coords.x / TILE_SIZE) * TILE_SIZE;
	x_interception += game->rays[ray_id].is_ray_facing_right * TILE_SIZE;
	y_interception = game->player.coords.y + (x_interception - game->player.coords.x) * tan(angle);
	x_step = TILE_SIZE;
	if (game->rays[ray_id].is_ray_facing_left == true)
		x_step *= -1;
	y_step = TILE_SIZE * tan(angle);
	if (y_step < 0 && game->rays[ray_id].is_ray_facing_down == true)
		y_step *= -1;
	if (y_step > 0 && game->rays[ray_id].is_ray_facing_up == true)
		y_step *= -1;
	while (x_interception >= 0 && x_interception < (game->width * TILE_SIZE) && 
		y_interception >= 0 && y_interception < (game->height * TILE_SIZE))
	{
		if (has_wall_at(game, x_interception - game->rays[ray_id].is_ray_facing_left, y_interception))
		{
			verticalX = x_interception;
			verticalY = y_interception;
			vertical_was_hit = true;
			break;
		}
		x_interception += x_step;
		y_interception += y_step;
	}
	/*CALCULATE DISTANCES*/
	if (horizontal_was_hit == true)
		horizontal_distance = calculate_hypo((horizontalX - game->player.coords.x), (horizontalY - game->player.coords.y));
	if (vertical_was_hit == true)
		vertical_distance = calculate_hypo((verticalX - game->player.coords.x), (verticalY - game->player.coords.y));
	if (vertical_distance < horizontal_distance)
	{
		game->rays[ray_id].coords.x = verticalX;
		game->rays[ray_id].coords.y = verticalY;
		game->rays[ray_id].coords.distance = vertical_distance;
	}
	else
	{
		game->rays[ray_id].coords.x = horizontalX;
		game->rays[ray_id].coords.y = horizontalY;
		game->rays[ray_id].coords.distance = horizontal_distance;
	}
	
}

static void	ray_constructor(t_game *game, int ray_id)
{
	game->rays[ray_id].was_hit_vertical = false;
	normalize_angle(&game->rays[ray_id].coords.angle);
	game->rays[ray_id].is_ray_facing_down = false;
	game->rays[ray_id].is_ray_facing_up = false;
	game->rays[ray_id].is_ray_facing_right = false;
	game->rays[ray_id].is_ray_facing_left = false;
	if (game->rays[ray_id].coords.angle > 0 && 
		game->rays[ray_id].coords.angle < M_PI)
		game->rays[ray_id].is_ray_facing_down = true;
	else
		game->rays[ray_id].is_ray_facing_up = true;
	if (game->rays[ray_id].coords.angle > M_PI + M_PI_2 || 
		game->rays[ray_id].coords.angle < M_PI_2)
		game->rays[ray_id].is_ray_facing_right = true;
	else
		game->rays[ray_id].is_ray_facing_left = true;
}

static void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, (M_PI + M_PI));
	if (*angle < 0)
		*angle = (M_PI + M_PI) + *angle;
}

static	double	calculate_hypo(double x, double y)
{
	return (sqrt(x * x + y * y));
}
