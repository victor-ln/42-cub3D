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

static void	draw_pixel(t_img *img, int x, int y, unsigned int color);
static void	draw_sprite(t_img *image, unsigned int color, int x, int y);
static void	draw_player(t_game *game);
static void draw_line(t_coord player, t_coord ray, t_img *img);

void	draw_game(t_game *game)
{
	register int		x;
	register int		y;

	y = 0;
	cast_all_rays(game);
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->params.map[y][x] == '0')
				draw_sprite(game->img, WHITE, (int)(x * TILE_SIZE), (int)(y * TILE_SIZE));
			else
				draw_sprite(game->img, BLACK, (int)(x * TILE_SIZE), (int)(y * TILE_SIZE));
			x++;
		}
		y++;
	}
	for (int i = 0; i < game->ray_nums; i++)
		draw_line(game->player.coords, game->rays[i].coords, game->img);
	draw_player(game);
}

static void	draw_player(t_game *game)
{
	int	y;
	int	x;

	y = -5;
	while (y < 5)
	{
		x = -5;
		while (x < 5)
		{
			draw_pixel(game->img, game->player.coords.wallHitX + x, \
				game->player.coords.wallHitY + y, RED);
			x++;
		}
		y++;
	}
}

static void draw_line(t_coord start, t_coord end, t_img *img)
{
	int		delta_x;
	int		delta_y;
	int		side_length;
	float	x_inc;
	float	y_inc;
	float	current_x;
	float	current_y;
	int		i;

	delta_x = (end.wallHitX - start.wallHitX);
	delta_y = (end.wallHitY - start.wallHitY);
	if (abs(delta_x) >= abs(delta_y))
		side_length = abs(delta_x);
	else
		side_length = abs(delta_y);
	x_inc = delta_x / (float)side_length;
	y_inc = delta_y / (float)side_length;
	current_x = start.wallHitX;
	current_y = start.wallHitY;
	i = 0;
	while (i < side_length)
	{
		draw_pixel(img, round(current_x), round(current_y), BLACK);
		current_x += x_inc;
		current_y += y_inc;
		i++;
	}
}

static void	draw_sprite(t_img *image, unsigned int color, int x, int y)
{
	register int		i;
	register int		j;

	j = 0;
	while (j < TILE_SIZE)
	{
		i = 0;
		while (i < TILE_SIZE)
		{
			draw_pixel(image, x + i, y + j, color);
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
