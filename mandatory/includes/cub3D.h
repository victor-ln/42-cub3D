/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3D.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/01 16:40:09 by adrianofaus	   #+#	#+#			 */
/*   Updated: 2022/08/24 17:25:24 by vlima-nu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3D_data.h"

void		save_params(t_game *game);

void		load_file(t_game *game, int argc, char *argv);

void		error(char *msg, t_game *game);

void		file_validate(t_game *game);

void		map_validate(t_game *game);

void		resize_line(t_game *game);

void		resize_column(t_game *game);

void		end_game(t_game *game);

int			get_textures(char *file_content, int identifier, t_game *game);

int			get_env_colors(char *file_content, int identifier, t_game *game);

int			get_map(char *file_content, t_game *game);

void		load_game(t_game *game);

int			close_window(t_game *game);

int			key_press_game(int keycode, t_game *game);

int			key_release(int keycode, t_game *game);

int			has_wall_at(t_game *game, double x, double y);

void		start_game(t_game *game);

void		cast_all_rays(t_game *game);

void		draw_pixel(t_image image, int x, int y, uint32_t color);

void		draw_line(t_image radar, t_texture_properties *properties);

void		draw_rectangle(t_image image, t_texture_properties *properties);

uint32_t	get_color(t_image image, int x, int y);

void		load_player(t_game *game);

void		load_rays(t_game *game);

size_t		get_max_line_size(char **map);

void		draw_3d_walls(t_game *game);

void		normalize_angle(double *angle);

void		ray_constructor(t_ray *ray);

double		calculate_hipo(double x, double y);

void		draw_ground_and_celling(t_game *game);

void		move_player(t_game *game);

void		load_textures(t_game *game);

int			load_sprite(t_image *image, void *mlx, char *path);

void		load_window(t_game *game);

void		load_images(t_game *game);

void		destroy_sprites(t_image *images, void *mlx, int x);

uint32_t	add_shade(uint32_t color, double scale);

void		free_game(t_game *game);

void		destroy_game(t_game *game);

#endif
