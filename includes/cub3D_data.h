/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:59:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/27 22:45:27 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DATA_H
# define CUB3D_DATA_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
# include "mlx.h"
# include "mlx_int.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>

# define INPUT_ERR			(void *)-1

# define MOVEMENT_SPEED		4
# define RAY_STRIP			1
# define TILE_SIZE			64

/*
	Field Of View angle is equals to 60 degrees
	times PI divided by 180 degrees.
*/
# define FOV_ANGLE			1.0471975511965977461542144610932

/*
	Rotation speed is equals to 4
	times PI divided by 180 degrees.
*/
# define STD_ROTATION_SPEED 0.03490658503988659153847381536977

# define RIGHT				1
# define LEFT				-1
# define DOWN				-1
# define UP					1

# define ESC				65307

/* COLORS */
# define RED				0xFF0000
# define BLACK				0x0
# define WHITE				0xFFFFFF

enum e_column_limits{
	TOP_LINE,
	BOT_LINE
};

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
	double			x;
	double			y;
	double			distance;
	double			angle;
}	t_coord;

typedef struct s_player
{
	t_coord	coords;
	double	rotation_speed;
	int		move_direction;
	int		walk_direction;
}	t_player;

typedef struct s_ray
{
	t_coord	coords;
	bool	was_hit_vertical;
	bool	is_ray_facing_down;
	bool	is_ray_facing_up;
	bool	is_ray_facing_right;
	bool	is_ray_facing_left;
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
	t_img		*img;
	t_img		*minimap;
	int			width;
	int			height;
	int			fov_radian;
	int			ray_nums;
	t_params	params;
	char		*file_content;
	char		*map_cub;
	t_ray		*rays;
	t_player	player;
}	t_game;

#endif
