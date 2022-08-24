/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:59:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/24 19:00:09 by afaustin         ###   ########.fr       */
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

# define MOVEMENT_SPEED			8
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
# define EPSILON				0.2

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

# define OBJECT_00				"./assets/xpm/objects/ammo.xpm"
# define OBJECT_01				"./assets/xpm/objects/armor.xpm"
# define OBJECT_02				"./assets/xpm/objects/barrel.xpm"
# define OBJECT_03				"./assets/xpm/objects/bed.xpm"
# define OBJECT_04				"./assets/xpm/objects/blood.xpm"
# define OBJECT_05				"./assets/xpm/objects/blue_key.xpm"
# define OBJECT_06				"./assets/xpm/objects/brass.xpm"
# define OBJECT_07				"./assets/xpm/objects/bucket.xpm"
# define OBJECT_08				"./assets/xpm/objects/bunch_skeletons.xpm"
# define OBJECT_09				"./assets/xpm/objects/cage.xpm"
# define OBJECT_10				"./assets/xpm/objects/cage_skeleton.xpm"
# define OBJECT_11				"./assets/xpm/objects/crown.xpm"
# define OBJECT_12				"./assets/xpm/objects/crucifix.xpm"
# define OBJECT_13				"./assets/xpm/objects/cup.xpm"
# define OBJECT_14				"./assets/xpm/objects/drinking_fountain.xpm"
# define OBJECT_15				"./assets/xpm/objects/empty_pit.xpm"
# define OBJECT_16				"./assets/xpm/objects/flag.xpm"
# define OBJECT_17				"./assets/xpm/objects/food_01.xpm"
# define OBJECT_18				"./assets/xpm/objects/food_02.xpm"
# define OBJECT_19				"./assets/xpm/objects/key.xpm"
# define OBJECT_20				"./assets/xpm/objects/lamp_01.xpm"
# define OBJECT_21				"./assets/xpm/objects/lamp_02.xpm"
# define OBJECT_22				"./assets/xpm/objects/lamp_03.xpm"
# define OBJECT_23				"./assets/xpm/objects/little_table.xpm"
# define OBJECT_24				"./assets/xpm/objects/machine_gun.xpm"
# define OBJECT_25				"./assets/xpm/objects/medkit.xpm"
# define OBJECT_26				"./assets/xpm/objects/oven.xpm"
# define OBJECT_27				"./assets/xpm/objects/pillar.xpm"
# define OBJECT_28				"./assets/xpm/objects/pitcher.xpm"
# define OBJECT_29				"./assets/xpm/objects/pit.xpm"
# define OBJECT_30				"./assets/xpm/objects/plant_01.xpm"
# define OBJECT_31				"./assets/xpm/objects/plant_02.xpm"
# define OBJECT_32				"./assets/xpm/objects/portrait.xpm"
# define OBJECT_33				"./assets/xpm/objects/pots_01.xpm"
# define OBJECT_34				"./assets/xpm/objects/pots_02.xpm"
# define OBJECT_35				"./assets/xpm/objects/puddle.xpm"
# define OBJECT_36				"./assets/xpm/objects/roots.xpm"
# define OBJECT_37				"./assets/xpm/objects/skeleton_blood.xpm"
# define OBJECT_38				"./assets/xpm/objects/skeleton.xpm"
# define OBJECT_39				"./assets/xpm/objects/skeleton_lying.xpm"
# define OBJECT_40				"./assets/xpm/objects/spears.xpm"
# define OBJECT_41				"./assets/xpm/objects/submachine_gun.xpm"
# define OBJECT_42				"./assets/xpm/objects/table_chairs.xpm"
# define OBJECT_43				"./assets/xpm/objects/trash_01.xpm"
# define OBJECT_44				"./assets/xpm/objects/trash_02.xpm"
# define OBJECT_45				"./assets/xpm/objects/trash_03.xpm"
# define OBJECT_46				"./assets/xpm/objects/treasure.xpm"

# define KNIFE_00				"./assets/xpm/weapons/knife_01.xpm"
# define KNIFE_01				"./assets/xpm/weapons/knife_02.xpm"
# define KNIFE_02				"./assets/xpm/weapons/knife_03.xpm"
# define KNIFE_03				"./assets/xpm/weapons/knife_04.xpm"
# define KNIFE_04				"./assets/xpm/weapons/knife_05.xpm"

// 384px 384px tamanho para editar em todos os sprites de armas
# define PISTOL_00				"./assets/xpm/weapons/pistol_01.xpm"
# define PISTOL_01				"./assets/xpm/weapons/pistol_02.xpm"
# define PISTOL_02				"./assets/xpm/weapons/pistol_03.xpm"
# define PISTOL_03				"./assets/xpm/weapons/pistol_04.xpm"
# define PISTOL_04				"./assets/xpm/weapons/pistol_05.xpm"

# define MACHINE_GUN_00				"./assets/xpm/weapons/machine_gun_01.xpm"
# define MACHINE_GUN_01				"./assets/xpm/weapons/machine_gun_02.xpm"
# define MACHINE_GUN_02				"./assets/xpm/weapons/machine_gun_03.xpm"
# define MACHINE_GUN_03				"./assets/xpm/weapons/machine_gun_04.xpm"
# define MACHINE_GUN_04				"./assets/xpm/weapons/machine_gun_05.xpm"

# define SUBMACHINE_GUN_00				"./assets/xpm/weapons/submachine_gun_01.xpm"
# define SUBMACHINE_GUN_01				"./assets/xpm/weapons/submachine_gun_02.xpm"
# define SUBMACHINE_GUN_02				"./assets/xpm/weapons/submachine_gun_03.xpm"
# define SUBMACHINE_GUN_03				"./assets/xpm/weapons/submachine_gun_04.xpm"
# define SUBMACHINE_GUN_04				"./assets/xpm/weapons/submachine_gun_05.xpm"

# define GUARD_00						"./assets/xpm/guard/front_idle_guard_01.xpm"
# define GUARD_01						"./assets/xpm/guard/backwards_idle_guard_01.xpm"
# define GUARD_02						"./assets/xpm/guard/shooting_guard_01.xpm"
# define GUARD_03						"./assets/xpm/guard/shooting_guard_02.xpm"
# define GUARD_04						"./assets/xpm/guard/dying_guard_01.xpm"
# define GUARD_05						"./assets/xpm/guard/dying_guard_02.xpm"
# define GUARD_06						"./assets/xpm/guard/dying_guard_03.xpm"
# define GUARD_07						"./assets/xpm/guard/dying_guard_04.xpm"
# define GUARD_08						"./assets/xpm/guard/dying_guard_05.xpm"

# define WEAPONS_TYPES			4
# define WEAPONS_FRAMES			5
# define OBJECTS_NUM			47
# define GUARD_NUM				9

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

typedef enum e_weapons {
	knife,
	pistol,
	machine_gun,
	submachine_gun
} t_weapons;

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

typedef struct s_sprites
{
	t_coord		coord;
	t_img		*img;
	bool		is_visible;
}	t_sprites;

typedef struct s_game
{
	void					*mlx;
	void					*window;
	int						window_width;
	int						window_height;
	int						ray_nums;
	int						doors_num;
	int						sprites_num;
	int						enemies_num;
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
	t_img					*weapons[WEAPONS_TYPES][WEAPONS_FRAMES];
	t_img					*enemy[GUARD_NUM];
	t_img					*objects[OBJECTS_NUM];
	t_texture_properties	*texture_prop;
	t_wall_properties		*wall_prop;
	t_rays_properties		*ray_prop;
	t_sprites				*sprites;
}	t_game;

#endif
