/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:59:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/16 21:00:01 by afaustin         ###   ########.fr       */
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
# include <stdint.h>
# include <limits.h>

# define INPUT_ERR				(void *)-1

# define MOVEMENT_SPEED			4
# define RAY_STRIP				1
# define TILE_SIZE				64
# define MINIMAP_SCALE_FACTOR	0.25

# define STD_WINDOW_WIDTH		1280
# define STD_WINDOW_HEIGHT		720
# define TEXTURES_NUM			4

/*
	Field Of View angle is equals to 60 degrees
	times PI divided by 180 degrees.
*/
# define FOV_ANGLE				1.0471975511965977461542144610932

/*
	Rotation speed is equals to 4
	times PI divided by 180 degrees.
*/
# define STD_ROTATION_SPEED 	0.03490658503988659153847381536977
# define STD_ROTATION_SPEED_M 	0.01745329251994329576923690768489

# define TURN_RIGHT				1
# define TURN_LEFT				-1
# define WALK_LEFT				-2
# define WALK_UP				1
# define WALK_RIGHT				2
# define WALK_DOWN				-1

# define ESC					65307
# define CTRL					65507
# define LEFT_CLICK				1
# define RIGHT_CLICK			2
# define SCROLL_UP				4
# define SCROLL_DOWN			5
# define ARROW_LEFT				65361
# define ARROW_UP				65362
# define ARROW_RIGHT			65363
# define ARROW_DOWN				65364

/* COLORS */
# define RED					0xFF0000
# define BLACK					0x0
# define WHITE					0xFFFFFF
# define GREEN					0x00FF00
# define BLUE					0x0000FF
# define MIDNIGHT_BLUE			0x191970
# define DARK_ORANGE			0xFF8C00
# define TRANSPARENCY			0xFF000000

# define GREEN_CROSSHAIR		"./assets/xpm/player/48px/crosshair_green.xpm"
# define RED_CROSSHAIR			"./assets/xpm/player/48px/crosshair_red.xpm"

# define LIGHT_FRONT_DOOR		"./assets/xpm/walls/iron_door_01.xpm"
# define DARK_FRONT_DOOR		"./assets/xpm/walls/iron_door_02.xpm"
# define LIGHT_SIDE_DOOR		"./assets/xpm/walls/iron_wall_02.xpm"
# define DARK_SIDE_DOOR			"./assets/xpm/walls/iron_wall_03.xpm"

typedef enum e_minimap_size{
	BIG,
	NORMAL
}	t_minimap_size;

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
	t_coord	coord;
	double	rotation_speed;
	int		move_direction;
	int		walk_direction;
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
	bool	is_ray_facing_down;
	bool	is_ray_facing_up;
	bool	is_ray_facing_right;
	bool	is_ray_facing_left;
	int		content_type;
}	t_ray;

typedef struct s_params
{
	char	**map;
	char	**textures;
	char	**rgb[2];
	int		environment[2];
}	t_params;

typedef struct s_minimap
{
	t_img				*radars[2];
	int					width;
	int					height;
	int					tile_size;
	int					widthpx;
	int					heightpx;
	t_minimap_size		minimap_size;
}	t_minimap;

typedef struct s_wall_properties
{
	float		proj_wall_height;
	float		proj_wall_dist;
	float		ray_distance;
	int			distance_from_top;
	u_int32_t	color_y;
	u_int32_t	color_x;
}	t_wall_properties;

typedef struct s_game
{
	void					*mlx;
	void					*window;
	int						window_width;
	int						window_height;
	int						ray_nums;
	int						doors_num;
	char					*file_content;
	char					*map_cub;
	t_ray					*rays;
	t_params				params;
	t_minimap				minimap;
	t_player				player;
	t_img					*img;
	t_img					*crosshair[2];
	t_img					*wall_textures[TEXTURES_NUM];
	t_img					*door_textures[TEXTURES_NUM];
	t_texture_properties	*texture_prop;
	t_wall_properties		*wall_prop;
	t_rays_properties		*ray_prop;
}	t_game;

#endif
