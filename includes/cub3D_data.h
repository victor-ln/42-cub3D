/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:59:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:47:03 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DATA_H
# define CUB3D_DATA_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <unistd.h>
# include "mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>

# define INPUT_ERR			(void *)-1
# define SPEED				2
# define RAY_STRIP			2
# define TILE_SIZE			32
# define FOV_ANGLE			60

enum e_environment{
	celling,
	ground
};

enum e_coords {
	NO,
	SO,
	WE,
	EA
};

typedef struct s_coord
{
	int		x;
	int		y;
	int		hipo;
	int		angle;
}	t_coord;

typedef struct s_player
{
	t_coord	coords;
	int		rotation_angle;
	int		rotation_speed;
	int		walk_dir;
	int		step_dir;
}	t_player;

typedef struct s_ray
{
	t_coord	coords;
}	t_ray;

typedef struct s_params
{
	char	**map;
	char	**textures;
	char	**rgb[2];
	int		environment[2];
}	t_params;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	void		*img;
	int			window_width;
	int			window_height;
	int			fov_radian;
	t_params	params;
	char		*file_content;
	char		*map_cub;
	t_ray		*rays;
}	t_game;

#endif
