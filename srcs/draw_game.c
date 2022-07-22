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
// static void	draw_ray(t_game *game, int i);

void	draw_game(t_game *game)
{
	register int		x;
	register int		y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->params.map[y][x] == '0')
				draw_sprite(game->img, WHITE, x * TILE_SIZE, y * TILE_SIZE);
			else
				draw_sprite(game->img, BLACK, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	draw_player(game);
	// for (int i = 0; i < game->ray_nums; i++)
	// 	draw_ray(game, i);
}

static void	draw_player(t_game *game)
{
	int	y;
	int	x;

	y = -10;
	while (y < 10)
	{
		x = -10;
		while (x < 10)
		{
			draw_pixel(game->img, game->player.coords.x + x, \
				game->player.coords.y + y, RED);
			x++;
		}
		y++;
	}
}

/*
static void	draw_ray(t_game *game, int i)
{
	float	dx, dy, step, x, y;

	x = game->player.coords.x;
	y = game->player.coords.y;
	dx = abs((int)x - game->rays[i].coords.x);
	dy = abs((int)y - game->rays[i].coords.y);
	if (dx >= dy)
		step = dx;
	else
		step = dy;
	dx = dx / step;
	dy = dy / step;
	i = 0;
	while (i < step)
	{
		draw_pixel(game->img, (int)x, (int)y, RED);
		x += dx;
		y += dy;
		i++;
	}
}
*/

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
