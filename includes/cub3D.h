/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:40:09 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/08/11 19:28:56 by afaustin         ###   ########.fr       */
/*                                                                            */
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

void		end_program(t_game *game);

int			get_textures(char *file_content, int identifier, t_game *game);

int			get_env_colors(char *file_content, int identifier, t_game *game);

int			get_map(char *file_content, t_game *game);

void		load_game(t_game *game);

int			reload_image(t_game *game);

int			close_window(t_game *game);

void		print_matrix(char **map);

int			key_press(int keycode, t_game *game);

int			key_release(int keycode, t_game *game);

int			has_wall_at(t_game *game, double x, double y);

void		start_game(t_game *game);

void		cast_all_rays(t_game *game);

void		draw_pixel(t_img *img, int x, int y, uint32_t color);

void		draw_line(t_img *radar, t_texture_properties *properties);

void		draw_rectangle(t_img *image, t_texture_properties *properties);

void		draw_radar(t_game *game);

void		draw_small_radar(t_game *game);

uint32_t	get_color(t_img *img, int x, int y);

void		load_player(t_game *game);

void		load_rays(t_game *game);

size_t		get_max_line_size(char **map);

void		draw_3d_walls(t_game *game);

void		normalize_angle(double *angle);

void		get_ray_content(t_game *game, int ray_id);

void		ray_constructor(t_game *game, int ray_id);

double		calculate_hipo(double x, double y);

int			mouse_click(int button, int x, int y, t_game *game);

void		draw_sprite(t_img *image, t_img *sprite, int x, int y);

void		save_doors_params(t_game *game);

#endif
