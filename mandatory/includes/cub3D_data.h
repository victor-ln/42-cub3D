/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:59:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/08 21:30:31 by vlima-nu         ###   ########.fr       */
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
# include "mlx_int.h"
# include "../../libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>

# define INPUT_ERR				(void *)-1

# define MOVEMENT_SPEED			4
# define RAY_STRIP				1
# define TILE_SIZE				64

# define STD_WINDOW_WIDTH_1		1280
# define STD_WINDOW_HEIGHT_1	720

# define STD_WINDOW_WIDTH_2		1024
# define STD_WINDOW_HEIGHT_2	768

# define STD_WINDOW_WIDTH_3		720
# define STD_WINDOW_HEIGHT_3	480

# define TEXTURES_NUM			4

/*
	Field Of View angle is equals to 60 degrees
	times PI divided by 180 degrees.
*/
# define FOV_ANGLE				1.0471975511965977461542144610932

/*
	Rotation speed is equals to 1
	times PI divided by 180 degrees.
*/
# define STD_ROTATION_SPEED_1 	0.01745329251994329576923690768489

/*
	Rotation speed is equals to 2
	times PI divided by 180 degrees.
*/
# define STD_ROTATION_SPEED_2 	0.03490658503988659153847381536977
/*
	Rotation speed is equals to 4
	times PI divided by 180 degrees.
*/
# define STD_ROTATION_SPEED_3	0.06981317007977318307694763073954
/*
	Rotation speed is equals to 6
	times PI divided by 180 degrees.
*/
# define STD_ROTATION_SPEED_4	0.10471975511965977461542144610932

# define HALF_PI				1.570796
# define PI						3.141592
# define PI_PLUS_HALF_PI		4.712388
# define TWO_PI					6.283185

# define TURN_RIGHT				1
# define TURN_LEFT				-1

# define WALK_LEFT				-1
# define WALK_UP				1
# define WALK_RIGHT				1
# define WALK_DOWN				-1

# define ESC					65307
# define SHIFT					65505
# define ARROW_LEFT				65361
# define ARROW_UP				65362
# define ARROW_RIGHT			65363
# define ARROW_DOWN				65364

/* COLORS */
# define TRANSPARENCY			0xFF000000
# define SHADE_NUMERATOR		600

enum e_leveling{
	horizontal,
	vertical
};

enum e_coord_enum{
	x,
	y
};

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

typedef struct s_image
{
	uint32_t	*buffer;
	t_img		*img;
}	t_image;

typedef struct s_img_properties
{
	uint32_t	color;
	int			width;
	int			height;
	int			offset_x;
	int			offset_y;
}	t_texture_properties;

typedef struct s_coord
{
	double			x;
	double			y;
	double			hipo;
	double			angle;
}	t_coord;

typedef struct s_player
{
	t_coord		coord;
	double		rotation_speed;
	int			movement_speed;
	int			move_direction;
	int			walk_direction;
	int			side_direction;
}	t_player;

typedef struct s_rays_properties
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	bool	was_hit;
	float	hipo;
}	t_rays_properties;

typedef struct s_ray
{
	t_coord	coord;
	bool	was_hit_vertical;
	bool	is_ray_facing_up;
	bool	is_ray_facing_left;
}	t_ray;

typedef struct s_params
{
	char	**map;
	char	**textures;
	char	**rgb[2];
	int		environment[2];
}	t_params;

typedef struct s_wall_properties
{
	float		proj_height;
	float		proj_wall_dist;
	float		ray_distance;
	int			distance_from_top;
	u_int32_t	color_y;
	u_int32_t	color_x;
}	t_wall_properties;

typedef struct s_game
{
	t_xvar					*mlx;
	t_win_list				*window;
	t_ray					*rays;
	t_rays_properties		ray_prop[2];
	long					ray_nums;
	int						window_width;
	int						window_height;
	long					half_height;
	long					half_width;
	t_texture_properties	texture_prop;
	t_wall_properties		wall_prop;
	t_player				player;
	t_params				params;
	t_image					img;
	t_image					wall_textures[TEXTURES_NUM];
	char					*file_content;
	char					*map_cub;
	int						minimap_heightpx;
	int						minimap_widthpx;
}	t_game;

#endif
