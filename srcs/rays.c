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

// static void		ray_constructor(t_game *game, int ray_id);
// static void		cast_ray(t_game *game, int ray_id);
// static	double	calculate_hypo(double x, double y);
void 			castRay(t_game *game, int stripId);
static void		normalize_angle(double *angle);
float 			distanceBetweenPoints(float x1, float y1, float x2, float y2);

void	cast_all_rays(t_game *game)
{
	int		i;
	float	angle;

	i = 0;
	angle = game->player.coords.rayAngle - (FOV_ANGLE / 2);
	while (i < game->ray_nums)
	{
		game->rays[i].coords.rayAngle = angle;
		castRay(game, i++);
		angle += FOV_ANGLE / game->ray_nums;
	}
}

void castRay(t_game *game, int stripId) {
	float	rayAngle;
    normalize_angle(&game->rays[stripId].coords.rayAngle);
	rayAngle = game->rays[stripId].coords.rayAngle;
    game->rays[stripId].isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    game->rays[stripId].isRayFacingUp = !game->rays[stripId].isRayFacingDown;

    game->rays[stripId].isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
    game->rays[stripId].isRayFacingLeft = !game->rays[stripId].isRayFacingRight;
    
    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    // int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(game->player.coords.wallHitY / TILE_SIZE) * TILE_SIZE;
    yintercept += game->rays[stripId].isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = game->player.coords.wallHitX + (yintercept - game->player.coords.wallHitY) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= game->rays[stripId].isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (game->rays[stripId].isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (game->rays[stripId].isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= (game->width * TILE_SIZE) && nextHorzTouchY >= 0 && nextHorzTouchY <= (game->height * TILE_SIZE)) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (game->rays[stripId].isRayFacingUp ? -1 : 0);
        
        if (has_wall_at(game, xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            // horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = true;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    
    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    // int vertWallContent = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(game->player.coords.wallHitX / TILE_SIZE) * TILE_SIZE;
    xintercept += game->rays[stripId].isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = game->player.coords.wallHitY + (xintercept - game->player.coords.wallHitX) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= game->rays[stripId].isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (game->rays[stripId].isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (game->rays[stripId].isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= (game->width * TILE_SIZE) && nextVertTouchY >= 0 && nextVertTouchY <= (game->height * TILE_SIZE)) {
        float xToCheck = nextVertTouchX + (game->rays[stripId].isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        
        if (has_wall_at(game, xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            // vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = true;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    float horzHitDistance = foundHorzWallHit
        ? distanceBetweenPoints(game->player.coords.wallHitX, game->player.coords.wallHitY, horzWallHitX, horzWallHitY)
        : __INT_MAX__;
    float vertHitDistance = foundVertWallHit
        ? distanceBetweenPoints(game->player.coords.wallHitX, game->player.coords.wallHitY, vertWallHitX, vertWallHitY)
        : __INT_MAX__;

    if (vertHitDistance < horzHitDistance) {
        game->rays[stripId].coords.distance = vertHitDistance;
        game->rays[stripId].coords.wallHitX = vertWallHitX;
        game->rays[stripId].coords.wallHitY = vertWallHitY;
        // game->rays[stripId].coords.wallHitContent = vertWallContent;
        game->rays[stripId].wasHitVertical = true;
    } else {
        game->rays[stripId].coords.distance = horzHitDistance;
        game->rays[stripId].coords.wallHitX = horzWallHitX;
        game->rays[stripId].coords.wallHitY = horzWallHitY;
        // game->rays[stripId].coords.wallHitContent = horzWallContent;
        game->rays[stripId].wasHitVertical = false;
    }
    game->rays[stripId].coords.rayAngle = rayAngle;
    game->rays[stripId].isRayFacingDown = game->rays[stripId].isRayFacingDown;
    game->rays[stripId].isRayFacingUp = game->rays[stripId].isRayFacingUp;
    game->rays[stripId].isRayFacingLeft = game->rays[stripId].isRayFacingLeft;
    game->rays[stripId].isRayFacingRight = game->rays[stripId].isRayFacingRight;
    // printf("\n\nPlayer: angle ==> %f x ==> %f y ==> %f\n", game->player.coords.rayAngle, game->player.coords.wallHitX, game->player.coords.wallHitY);
    // printf("\n\nRay: angle ==> %f x ==> %f y ==> %f\n", rayAngle, game->rays[stripId].coords.wallHitX, game->rays[stripId].coords.wallHitY);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// static void	cast_ray(t_game *game, int ray_id)
// {
// 	float	x_interception;
// 	float	y_interception;
// 	float	x_step;
// 	float	y_step;
// 	float	horizontalX;
// 	float	horizontalY;
// 	float	ray_angle;
// 	bool	horizontal_was_hit;
// 	float	horizontal_distance;

// 	float	verticalX;
// 	float	verticalY;
// 	bool	vertical_was_hit;
// 	float	vertical_distance;


// 	vertical_was_hit = false;
// 	horizontal_was_hit = false;
// 	vertical_distance = __INT_MAX__;
// 	horizontal_distance = __INT_MAX__;
// 	ray_constructor(game, ray_id);
// 	ray_angle = game->rays[ray_id].coords.angle;
// 	/*HORIZONTAL INTERCEPTION*/
// 	y_interception = floor(game->game->player.coords.coords.y / TILE_SIZE) * TILE_SIZE;
// 	x_interception = game->game->player.coords.coords.x + (y_interception - game->game->player.coords.coords.y) / tan(ray_angle);
// 	y_step = TILE_SIZE;
// 	if (game->rays[ray_id].is_facing_up == true)
// 		y_step *= -1;
// 	x_step = TILE_SIZE / tan(ray_angle);
// 	if (x_step < 0 && game->rays[ray_id].is_facing_right)
// 		x_step *= -1;
// 	if (x_step > 0 && game->rays[ray_id].is_facing_left)
// 		x_step *= -1;
// 	while (x_interception >= 0 && x_interception < (game->width * TILE_SIZE) && 
// 		y_interception >= 0 && y_interception < (game->height * TILE_SIZE))
// 	{
// 		if (has_wall_at(game, x_interception, y_interception - game->rays[ray_id].is_facing_up))
// 		{
// 			horizontalX = x_interception;
// 			horizontalY = y_interception;
// 			horizontal_was_hit = true;
// 			break;
// 		}
// 		x_interception += x_step;
// 		y_interception += y_step;
// 	}
// 	/*VERTICAL INTERCEPTION*/
// 	x_interception = floor(game->game->player.coords.coords.x / TILE_SIZE) * TILE_SIZE;
// 	y_interception = game->game->player.coords.coords.y + (x_interception - game->game->player.coords.coords.x) * tan(ray_angle);
// 	x_step = TILE_SIZE;
// 	if (game->rays[ray_id].is_facing_left == true)
// 		x_step *= -1;
// 	y_step = TILE_SIZE * tan(ray_angle);
// 	if (y_step < 0 && game->rays[ray_id].is_facing_down == true)
// 		y_step *= -1;
// 	if (y_step > 0 && game->rays[ray_id].is_facing_up == true)
// 		y_step *= -1;
// 	while (x_interception >= 0 && x_interception < (game->width * TILE_SIZE) && 
// 		y_interception >= 0 && y_interception < (game->height * TILE_SIZE))
// 	{
// 		if (has_wall_at(game, x_interception - game->rays[ray_id].is_facing_left, y_interception))
// 		{
// 			verticalX = x_interception;
// 			verticalY = y_interception;
// 			vertical_was_hit = true;
// 			break;
// 		}
// 		x_interception += x_step;
// 		y_interception += y_step;
// 	}
// 	/*CALCULATE DISTANCES*/
// 	if (horizontal_was_hit == true)
// 		horizontal_distance = calculate_hypo((horizontalX - game->game->player.coords.coords.x), (horizontalY - game->game->player.coords.coords.y));
// 	if (vertical_was_hit == true)
// 		vertical_distance = calculate_hypo((verticalX - game->game->player.coords.coords.x), (verticalY - game->game->player.coords.coords.y));
// 	if (vertical_distance < horizontal_distance)
// 	{
// 		game->rays[ray_id].coords.x = verticalX;
// 		game->rays[ray_id].coords.y = verticalY;
// 		game->rays[ray_id].coords.hipo = vertical_distance;
// 	}
// 	else
// 	{
// 		game->rays[ray_id].coords.x = horizontalX;
// 		game->rays[ray_id].coords.y = horizontalY;
// 		game->rays[ray_id].coords.hipo = horizontal_distance;
// 	}
// }

// static void	ray_constructor(t_game *game, int ray_id)
// {
// 	game->rays[ray_id].was_hit_vertical = false;
// 	normalize_angle(&game->rays[ray_id].coords.angle);
// 	game->rays[ray_id].is_facing_down = false;
// 	game->rays[ray_id].is_facing_up = false;
// 	game->rays[ray_id].is_facing_right = false;
// 	game->rays[ray_id].is_facing_left = false;
// 	if (game->rays[ray_id].coords.angle > 0 && 
// 		game->rays[ray_id].coords.angle < M_PI)
// 		game->rays[ray_id].is_facing_down = true;
// 	else
// 		game->rays[ray_id].is_facing_up = true;
// 	if (game->rays[ray_id].coords.angle > M_PI + M_PI_2 || 
// 		game->rays[ray_id].coords.angle < M_PI_2)
// 		game->rays[ray_id].is_facing_right = true;
// 	else
// 		game->rays[ray_id].is_facing_left = true;
// }

static void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, (M_PI + M_PI));
	if (*angle < 0)
		*angle = (M_PI + M_PI) + *angle;
}

// static	double	calculate_hypo(double x, double y)
// {
// 	return (sqrt(x * x + y * y));
// }