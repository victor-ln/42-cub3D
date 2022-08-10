/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw_3d_walls.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/08/04 21:00:02 by vlima-nu		  #+#	#+#			 */
/*   Updated: 2022/08/04 21:15:22 by vlima-nu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3D.h"

static int	get_texture_id(t_game *game, int col);
static void	get_texture_properties(t_game *game, int col);
static void	get_wall_dimension(t_game *game, int col);
static void	get_texture_coordinates(t_game *game, int col, int line);

void	draw_3d_walls(t_game *game)
{
	int		col;
	int		line;
	int		texture_id;

	col = 0;
	while (col < game->ray_nums)
	{
		get_wall_dimension(game, col);
		get_texture_properties(game, col);
		texture_id = get_texture_id(game, col);
		line = game->texture_prop->offset_y;
		while (line < game->texture_prop->height)
		{
			get_texture_coordinates(game, col, line);
			draw_pixel(game->img, col, line, \
				get_color(game->wall_textures[texture_id], \
				game->wall_prop->color_x, game->wall_prop->color_y));
			line++;
		}
		col++;
	}
}

static void	get_texture_coordinates(t_game *game, int col, int line)
{
	if (game->rays[col].was_hit_vertical)
		game->wall_prop->color_x = (int)game->rays[col].coord.y % (TILE_SIZE);
	else
		game->wall_prop->color_x = (int)game->rays[col].coord.x % (TILE_SIZE);
	game->wall_prop->distance_from_top = line + \
	((int)game->wall_prop->proj_wall_height / 2) - (game->window_height / 2);
	game->wall_prop->color_y = game->wall_prop->distance_from_top * \
		((float)TILE_SIZE / (int)game->wall_prop->proj_wall_height);
}

static void	get_wall_dimension(t_game *game, int col)
{
	game->wall_prop->ray_distance = game->rays[col].coord.hipo * \
		cos(game->rays[col].coord.angle - game->player.coord.angle);
	game->wall_prop->proj_wall_dist = (game->window_width / 2) \
		/ tan(FOV_ANGLE / 2);
	game->wall_prop->proj_wall_height = \
		(TILE_SIZE / game->wall_prop->ray_distance) * \
		game->wall_prop->proj_wall_dist;
}

static void	get_texture_properties(t_game *game, int col)
{
	game->texture_prop->offset_y = (game->window_height / 2) - \
		((int)game->wall_prop->proj_wall_height / 2);
	if (game->texture_prop->offset_y < 0)
		game->texture_prop->offset_y = 0;
	game->texture_prop->offset_x = col * RAY_STRIP;
	game->texture_prop->width = RAY_STRIP;
	game->texture_prop->height = (game->window_height / 2) + \
		((int)game->wall_prop->proj_wall_height / 2);
	if (game->texture_prop->height > game->window_height)
		game->texture_prop->height = game->window_height;
}

static int	get_texture_id(t_game *game, int col)
{
	int		texture_id;

	if (game->rays[col].was_hit_vertical)
	{
		if (game->rays[col].is_ray_facing_right)
			texture_id = EA;
		else
			texture_id = WE;
	}
	else
	{
		if (game->rays[col].is_ray_facing_up)
			texture_id = NO;
		else
			texture_id = SO;
	}
	return (texture_id);
}
