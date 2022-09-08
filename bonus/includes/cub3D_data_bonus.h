/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:59:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 20:41:15 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DATA_BONUS_H
# define CUB3D_DATA_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
# include "mlx.h"
# include "mlx_int_bonus.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <sys/time.h>
# include <time.h>
# include "menu_bonus.h"

# define INPUT_ERR				(void *)-1

# define MOVEMENT_SPEED			8
# define RAY_STRIP				1
# define TILE_SIZE				64

# define MINIMAP_TILE_SIZE		16
# define MINIMAP_SCALE_FACTOR	0.25

# define STD_WINDOW_WIDTH_1		1280
# define STD_WINDOW_HEIGHT_1	720

# define STD_WINDOW_WIDTH_2		1024
# define STD_WINDOW_HEIGHT_2	768

# define STD_WINDOW_WIDTH_3		720
# define STD_WINDOW_HEIGHT_3	480

# define TEXTURES_NUM			4
# define FPS_RATE				30.0f

/*
	Field Of View angle is equals to 60 degrees
	times PI divided by 180 degrees.
*/
# define FOV_ANGLE				1.0471975511965977461542144610932
# define EPSILON				0.2

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

# define TURN_RIGHT				1
# define TURN_LEFT				-1

# define WALK_LEFT				-2
# define WALK_UP				1
# define WALK_RIGHT				2
# define WALK_DOWN				-1

# define ESC					65307
# define CTRL					65507
# define SHIFT					65505
# define LEFT_CLICK				1
# define RIGHT_CLICK			2
# define SCROLL_UP				4
# define SCROLL_DOWN			5
# define ARROW_LEFT				65361
# define ARROW_UP				65362
# define ARROW_RIGHT			65363
# define ARROW_DOWN				65364
# define ENTER_1				65293
# define ENTER_2				65421

/* COLORS */
# define RED					0xFF0000
# define BLACK					0x0
# define WHITE					0xFFFFFF
# define GREEN					0x00FF00
# define BLUE					0x0000FF
# define MIDNIGHT_BLUE			0x191970
# define DARK_ORANGE			0xFF8C00
# define TRANSPARENCY			0xFF000000

# define WEAPONS_TYPES			4
# define WEAPONS_FRAMES			5
# define OBJECTS_NUM			47
# define GUARD_NUM				9

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

typedef enum e_weapons {
	knife,
	pistol,
	machine_gun,
	submachine_gun
}	t_weapons;

enum e_guard {
	front_idle_guard,
	backwards_idle_guard,
	shooting_guard_01,
	shooting_guard_02,
	dying_guard_01,
	dying_guard_02,
	dying_guard_03,
	dying_guard_04,
	dying_guard_05
};

enum e_objects {
	ammo,
	armor,
	barrel,
	bed,
	blood,
	blue_key,
	brass,
	bucket,
	bunch_skeletons,
	cage,
	cage_skeleton,
	crown,
	crucifix,
	cup,
	drinking_fountain,
	empty_pit,
	flag,
	food_01,
	food_02,
	key,
	lamp_01,
	lamp_02,
	lamp_03,
	little_table,
	machine_gun_item,
	medkit,
	oven,
	pillar,
	pitcher,
	pit,
	plant_01,
	plant_02,
	portrait,
	pots_01,
	pots_02,
	puddle,
	roots,
	skeleton_blood,
	skeleton,
	skeleton_lying,
	spears,
	submachine_gun_item,
	table_chairs,
	trash_01,
	trash_02,
	trash_03,
	treasure
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
	t_weapons	weapon;
	int			weapon_frame;
	bool		is_shooting;
	bool		has_shooted;
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
	t_image				radars;
	int					width;
	int					height;
	int					widthpx;
	int					heightpx;
	int					small_radar_limit_x;
	int					small_radar_limit_y;
	int					small_radar_widthpx;
	int					small_radar_heightpx;
}	t_minimap;

typedef struct s_wall_properties
{
	float		proj_height;
	float		proj_wall_dist;
	float		ray_distance;
	int			distance_from_top;
	u_int32_t	color_y;
	u_int32_t	color_x;
}	t_wall_properties;

typedef struct s_sprites
{
	t_coord		coord;
	t_image		img;
	bool		is_visible;
	bool		is_enemy;
	int			enemy_index;
}	t_sprites;

typedef struct s_enemy
{
	int			enemy_index;
	bool		is_dead;
	int			enemy_frame;
}	t_enemy;

typedef struct s_fps
{
	clock_t				ticks_last_frame;
	double				fps_length;
	double				delta;
	int					frames;
	char				*fps_string;
	int					fps_offset_x;
	int					fps_offset_y;
}	t_fps;

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
	t_fps					fps;
	long					sprites_num;
	long					visible_sprites_num;
	long					enemies_num;
	long					enemy_spotted;
	t_texture_properties	texture_prop;
	t_wall_properties		wall_prop;
	t_minimap				minimap;
	t_player				player;
	t_params				params;
	t_image					img;
	t_image					crosshair[2];
	t_image					wall_textures[TEXTURES_NUM];
	t_image					door_textures[TEXTURES_NUM];
	t_image					weapons[WEAPONS_TYPES][WEAPONS_FRAMES];
	t_image					enemy[GUARD_NUM];
	t_image					objects[OBJECTS_NUM];
	t_sprites				*sprites;
	t_sprites				*visible_sprites;
	t_enemy					*enemies;
	char					*file_content;
	char					*map_cub;
	bool					is_on_the_game;
	t_image					options_menu[18];
	t_image					selection_menu[10];
	int						frame;
	t_menu					menu;
}	t_game;

#endif
