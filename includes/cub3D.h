/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:40:09 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/13 18:54:08 by afaustin         ###   ########.fr       */
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

void	print_matrix(char **map);

#endif
