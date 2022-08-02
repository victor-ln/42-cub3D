/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_radar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:40:03 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/01 21:06:22 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static void draw_field_of_view(t_game *game);
static void draw_environment(t_game *game);
static void draw_player(t_game *game);
static void	draw_small_radar(t_game *game);

void	draw_radar(t_game *game)
{
    draw_environment(game);
    draw_player(game);
    draw_field_of_view(game);
	if (game->map_size == BIG)
		draw_small_radar(game);
}

static void	draw_small_radar(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = floor(game->player.coords.y - 160);
	x = floor(game->player.coords.x - 90);
	while (i < 22)
	{
		j = 0;
		while (j < 40)
		{
			draw_pixel(game->small_radar, j * TILE_SIZE * MINIMAP_SCALE_FACTOR, i * TILE_SIZE * MINIMAP_SCALE_FACTOR, get_color(game->radar, x + (j * MINIMAP_SCALE_FACTOR * TILE_SIZE), y + (i * MINIMAP_SCALE_FACTOR * TILE_SIZE)));
			j++;
		}
		i++;
	}
}

// void    draw_sprite(t_img *image, t_img *sprite, int x, int y)
// {
//     register int        i;
//     register int        j;

//     j = 0;
//     while (j < sprite->height)
//     {
//         i = 0;
//         while (i < sprite->width)
//         {
//             draw_pixel(image, x + i, y + j, get_color(sprite, i, j));
//             i++;
//         }
//         j++;
//     }
// }

static void	draw_field_of_view(t_game *game)
{
    int     i;

    i = 0;
    game->img_properties->color = RED;
	game->img_properties->offset_x = game->player.coords.x * MINIMAP_SCALE_FACTOR;
	game->img_properties->offset_y = game->player.coords.y * MINIMAP_SCALE_FACTOR;
	while (i < game->ray_nums)
	{
		game->img_properties->width = game->rays[i].coords.x * MINIMAP_SCALE_FACTOR;
		game->img_properties->height = game->rays[i].coords.y * MINIMAP_SCALE_FACTOR;
		draw_line(game->radar, game->img_properties);
		i++;
	}
}

static void	draw_environment(t_game *game)
{
	int					x;
	int					y;

	game->img_properties->height = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	game->img_properties->width = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		game->img_properties->offset_y = TILE_SIZE * y * MINIMAP_SCALE_FACTOR;
		while (game->params.map[y][x])
		{
			game->img_properties->offset_x = TILE_SIZE * x * MINIMAP_SCALE_FACTOR;
			game->img_properties->color = BLACK;
			if (game->params.map[y][x] == '0')
			{
				game->img_properties->color = WHITE;
				draw_rectangle(game->radar, game->img_properties);
			}
			else
				draw_rectangle(game->radar, game->img_properties);
			x++;
		}
		y++;
	}
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
			draw_pixel(
				game->radar,
				(game->player.coords.x + x) * MINIMAP_SCALE_FACTOR, 
				(game->player.coords.y + y) * MINIMAP_SCALE_FACTOR,
				RED
			);
			x++;
		}
		y++;
	}
}
