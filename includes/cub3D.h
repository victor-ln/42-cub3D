/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:40:09 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/08/01 22:02:40 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3D_data.h"

void	save_params(t_game *game);

void	load_file(t_game *game, int argc, char *argv);

void	error(char *msg, t_game *game);

void	file_validate(t_game *game);

void	map_validate(t_game *game);

void	resize_line(t_game *game);

void	resize_column(t_game *game);

void	end_program(t_game *game);

int		get_textures(char *file_content, int identifier, t_game *game);

int		get_env_colors(char *file_content, int identifier, t_game *game);

int		get_map(char *file_content, t_game *game);

void	load_game(t_game *game);

int		reload_image(t_game *game);

int		close_window(t_game *game);

void	print_matrix(char **map);

int		key_press(int keycode, t_game *game);

int		key_release(int keycode, t_game *game);

int		has_wall_at(t_game *game, double x, double y);

void	start_game(t_game *game);

void	cast_all_rays(t_game *game);

void	draw_pixel(t_img *img, int x, int y, unsigned int color);

void    draw_line(t_img *radar, t_img_properties *properties);

void	draw_rectangle(t_img *image, t_img_properties *properties);

void	draw_radar(t_game *game);

unsigned int    get_color(t_img *img, int x, int y);

#endif
