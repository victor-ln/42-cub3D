/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:21:14 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:21:14 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef	struct s_image_properties
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	color;
	unsigned int	offset_x;
	unsigned int	offset_y;
}	t_image_properties;

static void	draw_pixel(t_img *img, int x, int y, unsigned int color);
void	draw_3d_walls(t_game *game);
static void	draw_rectangle(t_img *image, t_image_properties properties);
void	draw_ground_and_celling(t_game *game);
// static void	draw_player(t_game *game);
// static void draw_line(t_coord player, t_coord ray, t_img *img);

void	draw_game(t_game *game)
{
	// int		i;

	// i = 0;
	cast_all_rays(game);
	// draw_minimap(game);
	// while (i < game->ray_nums)
	// 	draw_line(game->player.coords, game->rays[i++].coords, game->minimap);
	// draw_player(game);
	draw_ground_and_celling(game);
	if (!game->mlx)
		draw_3d_walls(game);
}

void	draw_ground_and_celling(t_game *game)
{
	t_image_properties properties;

	properties.color = BLACK;
	properties.offset_x = 0;
	properties.offset_y = 0;
	properties.height = game->height * TILE_SIZE / 2;
	properties.width = game->width * TILE_SIZE;
	draw_rectangle(game->img, properties);
	properties.color = WHITE;
	properties.offset_x = 0;
	properties.offset_y = game->height * TILE_SIZE / 2;
	properties.height = game->height * TILE_SIZE / 2;
	properties.width = game->width * TILE_SIZE;
	draw_rectangle(game->img, properties);
}

// static void	draw_minimap(t_game *game)
// {
// 	t_image_properties properies;

// 	properies.height = TILE_SIZE;
// 	properies.width = TILE_SIZE;
// 	properies.y = 0;
// 	while (properies.y < game->height)
// 	{
// 		x = 0;
// 		properies.x = 0;
// 		while (properies.x < game->width)
// 		{
// 			properies.color = BLACK;
// 			if (game->params.map[properies.y][properies.x] == '0')
// 			{
// 				properies.color = WHITE;
// 				draw_rectangle(game->minimap, properies);
// 			}
// 			else
// 				draw_rectangle(game->minimap, properies);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	draw_player(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	y = -5;
// 	while (y < 5)
// 	{
// 		x = -5;
// 		while (x < 5)
// 		{
// 			draw_pixel(game->minimap game->player.coords.x + x, 
// 				game->player.coords.y + y, RED);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void draw_line(t_coord start, t_coord end, t_img *img)
// {
// 	int		delta_x;
// 	int		delta_y;
// 	int		side_length;
// 	float	x_inc;
// 	float	y_inc;
// 	float	current_x;
// 	float	current_y;
// 	int		i;

// 	delta_x = (end.x - start.x);
// 	delta_y = (end.y - start.y);
// 	if (abs(delta_x) >= abs(delta_y))
// 		side_length = abs(delta_x);
// 	else
// 		side_length = abs(delta_y);
// 	x_inc = delta_x / (float)side_length;
// 	y_inc = delta_y / (float)side_length;
// 	current_x = start.x;
// 	current_y = start.y;
// 	i = 0;
// 	while (i < side_length)
// 	{
// 		draw_pixel(img, round(current_x), round(current_y), BLACK);
// 		current_x += x_inc;
// 		current_y += y_inc;
// 		i++;
// 	}
// }

static void	draw_rectangle(t_img *image, t_image_properties properties)
{
	unsigned int		i;
	unsigned int		j;

	j = properties.offset_y;
	while (j < properties.height)
	{
		i = properties.offset_x;
		while (i < properties.width)
		{
			draw_pixel(image, i, j, properties.color);
			i++;
		}
		j++;
	}
}

static void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	*(unsigned int *)
		((img->data + (x * img->bpp / 8 + y * img->size_line))) = color;
}

void	draw_3d_walls(t_game *game)
{
	t_image_properties	properties;
	int					column;
	float				projected_wall_dist;
	float				projected_wall_height;
	float				ray_distance;

	column = 0;
	while (column < game->ray_nums)
	{
		ray_distance = game->rays[column].coords.distance * \
			cos(game->rays[column].coords.angle - game->player.coords.angle);
		projected_wall_dist = (game->width * TILE_SIZE) / 2 / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / ray_distance) * projected_wall_dist;
		properties.color = (RED << 8) | (unsigned int)(100 / game->rays[column].coords.distance);
		properties.offset_x = column * RAY_STRIP;
		properties.offset_y = (game->height * TILE_SIZE - projected_wall_height) / 2;
		properties.width = RAY_STRIP;
		properties.height = projected_wall_height;
		draw_rectangle(game->img, properties);
		column++;
	}
}
