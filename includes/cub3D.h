/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:40:09 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/11 18:55:02 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3D_data.h"

void	save_params(t_game *game);

char	*load_file(int argc, char *argv);

void	print_and_exit(char *msg, t_game *game);

void	file_validate(t_game *game);

void	map_validate(t_game *game);

#endif
