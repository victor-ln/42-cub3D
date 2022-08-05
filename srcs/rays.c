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

static void 	cast_ray(t_game *game, int ray_id);

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
	float	angle;
	bool	horizontal_was_hit;
	float	horizontal_distance;
	bool	vertical_was_hit;
	float	vertical_distance;

	vertical_was_hit = false;
	horizontal_was_hit = false;
	vertical_distance = __FLT_MAX__;
	horizontal_distance = __FLT_MAX__;
	/*HORIZONTAL INTERCEPTION*/
	
	/*VERTICAL INTERCEPTION*/
	x_interception = floor(game->player.coord.x / TILE_SIZE) * TILE_SIZE;
	x_interception += game->rays[ray_id].is_ray_facing_right * TILE_SIZE;
	y_interception = game->player.coord.y + (x_interception - game->player.coord.x) * tan(angle);
	x_step = TILE_SIZE;
	if (game->rays[ray_id].is_ray_facing_left == true)
		x_step *= -1;
	y_step = TILE_SIZE * tan(angle);
	if (y_step < 0 && game->rays[ray_id].is_ray_facing_down == true)
		y_step *= -1;
	if (y_step > 0 && game->rays[ray_id].is_ray_facing_up == true)
		y_step *= -1;
	while (x_interception >= 0 && x_interception < (game->minimap.width * TILE_SIZE) && 
		y_interception >= 0 && y_interception < (game->minimap.height * TILE_SIZE))
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
		horizontal_distance = calculate_hypo((horizontalX - game->player.coord.x), (horizontalY - game->player.coord.y));
	if (vertical_was_hit == true)
		vertical_distance = calculate_hypo((verticalX - game->player.coord.x), (verticalY - game->player.coord.y));
	if (vertical_distance < horizontal_distance)
	{
		game->rays[ray_id].coord.x = verticalX;
		game->rays[ray_id].coord.y = verticalY;
		game->rays[ray_id].coord.distance = vertical_distance;
		game->rays[ray_id].was_hit_vertical = true;
	}
	else
	{
		game->rays[ray_id].coord.x = horizontalX;
		game->rays[ray_id].coord.y = horizontalY;
		game->rays[ray_id].coord.distance = horizontal_distance;
	}
	
}

static void	cast_vertical(t_game *game, int ray_id)
{
	float	verticalX;
	float	verticalY;
}

static void	cast_horizontal(t_game *game, int ray_id)
{
	float	horizontalX;
	float	horizontalY;

	game->ray_prop[horizontal].y_interception = floor(game->player.coord.y / TILE_SIZE) * TILE_SIZE;
	game->ray_prop[horizontal].y_interception += game->rays[ray_id].is_ray_facing_down * TILE_SIZE;
	game->ray_prop[horizontal].x_interception = game->player.coord.x + (game->ray_prop[horizontal].y_interception - game->player.coord.y) / tan(angle);
	game->ray_prop[horizontal].y_step = TILE_SIZE;
	if (game->rays[ray_id].is_ray_facing_up == true)
		game->ray_prop[horizontal].y_step *= -1;
	game->ray_prop[horizontal].x_step = TILE_SIZE / tan(game->rays[ray_id].coord.angle);
	if (game->ray_prop[horizontal].x_step < 0 && game->rays[ray_id].is_ray_facing_right)
		game->ray_prop[horizontal].x_step *= -1;
	if (game->ray_prop[horizontal].x_step > 0 && game->rays[ray_id].is_ray_facing_left)
		game->ray_prop[horizontal].x_step *= -1;
	while (game->ray_prop[horizontal].x_interception >= 0 && game->ray_prop[horizontal].x_interception < (game->minimap.width * TILE_SIZE) && 
		game->ray_prop[horizontal].y_interception >= 0 && game->ray_prop[horizontal].y_interception < (game->minimap.height * TILE_SIZE))
	{
		if (has_wall_at(game, game->ray_prop[horizontal].x_interception, game->ray_prop[horizontal].y_interception - game->rays[ray_id].is_ray_facing_up))
		{
			horizontalX = game->ray_prop[horizontal].x_interception;
			horizontalY = game->ray_prop[horizontal].y_interception;
			game->ray_prop[horizontal].was_hit = true;
			break;
		}
		game->ray_prop[horizontal].x_interception += game->ray_prop[horizontal].x_step;
		game->ray_prop[horizontal].y_interception += game->ray_prop[horizontal].y_step;
	}
}
