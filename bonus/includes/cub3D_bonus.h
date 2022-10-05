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

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3D_data_bonus.h"

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

void		draw_radar(t_game *game);

void		draw_small_radar(t_game *game);

uint32_t	get_color(t_image image, int x, int y);

void		load_player(t_game *game);

void		load_rays(t_game *game);

size_t		get_max_line_size(char **map);

void		draw_3d_walls(t_game *game);

void		normalize_angle(double *angle);

void		get_ray_content(t_game *game, t_ray *ray);

void		ray_constructor(t_ray *ray);

double		calculate_hipo(double x, double y);

int			mouse_click(int button, int x, int y, t_game *game);

void		draw_sprite(t_image image, t_image sprite, int x, int y);

void		doors_validate(t_game *game);

void		open_door(t_game *game);

void		draw_ground_and_celling(t_game *game);

void		draw_crosshair(t_game *game);

void		draw_weapon(t_game *game);

void		get_visible_sprites(t_game *game);

void		save_sprites(t_game *game);

void		draw_visible_sprites(t_game *game);

int			mouse_release(int button, int x, int y, t_game *game);

void		move_player(t_game *game);

int			mouse_move(int x, int y, t_game *game);

void		start_time(t_game *game);

void		count_fps(t_game *game);

void		load_textures(t_game *game);

bool		is_enemy_spotted(t_game *game, int i);

void		kill_enemy(t_game *game, int i);

void		qsort_recursive(t_sprites *sprites, int start, int end);

int			load_sprite(t_image *image, void *mlx, char *path);

void		load_menus(t_game *game);

int			key_press_menu(int key_code, t_game *game);

void		load_window(t_game *game);

void		load_images(t_game *game);

void		destroy_sprites(t_image *images, void *mlx, int x);

uint32_t	add_shade(uint32_t color, double scale);

void		free_game(t_game *game);

void		destroy_game(t_game *game);

void		apply_changes(t_game *game);

int			set_resolution(t_game *game);

void		change_menu(t_menu *menu, t_menu_screen menu_screen);

int			manipulate_ray_axis(t_game *game, int x, int y, int axis);

void		calculate_next_step(t_game *game, int move_step, int side_step);

int         is_obj(char c);

#endif
