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

static t_img	*get_texture_id(t_game *game, int col);
static void		get_texture_properties(t_game *game, int col);
static void		get_wall_dimension(t_game *game, int col);
static void		get_texture_coordinates(t_game *game, int col, int line);

void	draw_3d_walls(t_game *game)
{
	int		col;
	int		line;
	t_img	*current_img;

	col = 0;
	while (col < game->ray_nums)
	{
		get_wall_dimension(game, col);
		get_texture_properties(game, col);
		current_img = get_texture_id(game, col);
		line = game->texture_prop.offset_y;
		while (line < game->texture_prop.height)
		{
			get_texture_coordinates(game, col, line);
			draw_pixel(game->img, col, line, \
				add_shade(get_color(current_img, \
				game->wall_prop.color_x, game->wall_prop.color_y), 
				600 / game->rays[col].coord.hipo));
			line++;
		}
		col++;
	}
}

static void	get_texture_coordinates(t_game *game, int col, int line)
{
	if (game->rays[col].was_hit_vertical)
		game->wall_prop.color_x = (int)game->rays[col].coord.y % (TILE_SIZE);
	else
		game->wall_prop.color_x = (int)game->rays[col].coord.x % (TILE_SIZE);
	game->wall_prop.distance_from_top = line + \
	((int)game->wall_prop.proj_height / 2) - (game->half_height);
	game->wall_prop.color_y = game->wall_prop.distance_from_top * \
		((float)TILE_SIZE / (int)game->wall_prop.proj_height);
}

static void	get_wall_dimension(t_game *game, int col)
{
	game->wall_prop.ray_distance = game->rays[col].coord.hipo * \
		cos(game->rays[col].coord.angle - game->player.coord.angle);
	game->wall_prop.proj_wall_dist = (game->half_width) \
		/ tan(FOV_ANGLE / 2);
	game->wall_prop.proj_height = \
		(TILE_SIZE / game->wall_prop.ray_distance) * \
		game->wall_prop.proj_wall_dist;
}

static void	get_texture_properties(t_game *game, int col)
{
	game->texture_prop.offset_y = (game->half_height) - \
		((int)game->wall_prop.proj_height / 2);
	if (game->texture_prop.offset_y < 0)
		game->texture_prop.offset_y = 0;
	game->texture_prop.offset_x = col * RAY_STRIP;
	game->texture_prop.width = RAY_STRIP;
	game->texture_prop.height = (game->half_height) + \
		((int)game->wall_prop.proj_height / 2);
	if (game->texture_prop.height > game->window_height)
		game->texture_prop.height = game->window_height;
}

static t_img	*get_texture_id(t_game *game, int col)
{
	if (game->rays[col].content_type == 'O')
	{
		if (game->rays[col].was_hit_vertical)
			return (game->door_textures[2]);
		return (game->door_textures[3]);
	}
	if (game->rays[col].content_type == 'D')
	{
		if (game->rays[col].was_hit_vertical)
			return (game->door_textures[0]);
		return (game->door_textures[1]);
	}
	else if (game->rays[col].was_hit_vertical)
	{
		if (game->rays[col].is_ray_facing_left)
			return (game->wall_textures[WE]);
		return (game->wall_textures[EA]);
	}
	else
	{
		if (game->rays[col].is_ray_facing_up)
			return (game->wall_textures[NO]);
		return (game->wall_textures[SO]);
	}
}
