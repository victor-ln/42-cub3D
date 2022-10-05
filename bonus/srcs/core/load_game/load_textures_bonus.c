/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:33:40 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/10/04 20:42:42 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "assets_bonus.h"

static int	load_all_groups(t_game *game);
static int	load_env_textures(t_game *game);
static int	load_sprite_group(t_image *ptr, void *mlx, char *path, int size);

void	load_textures(t_game *game)
{
	int		status;

	status = load_sprite(game->wall_textures + NO, game->mlx, \
		game->params.textures[NO]);
	status += load_sprite(game->wall_textures + SO, game->mlx, \
		game->params.textures[SO]);
	status += load_sprite(game->wall_textures + WE, game->mlx, \
		game->params.textures[WE]);
	status += load_sprite(game->wall_textures + EA, game->mlx, \
		game->params.textures[EA]);
	status += load_all_groups(game);
	status += load_env_textures(game);
	if (status != EXIT_SUCCESS)
		error("Could not load textures", game);
}

int	load_sprite(t_image *image, void *mlx, char *path)
{
	int		height;
	int		width;

	image->img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!image->img)
		return (1);
	image->img->height = height;
	image->img->width = width;
	image->img->bpp /= 8;
	image->img->size_line /= image->img->bpp;
	image->buffer = (uint32_t *)image->img->data;
	return (0);
}

static int	load_env_textures(t_game *game)
{
	int	status;

	status = load_sprite(game->crosshair, game->mlx, GREEN_CROSSHAIR);
	status += load_sprite(game->crosshair + 1, game->mlx, RED_CROSSHAIR);
	status += load_sprite(game->door_textures, game->mlx, LIGHT_FRONT_DOOR);
	status += load_sprite(game->door_textures + 1, game->mlx, DARK_FRONT_DOOR);
	status += load_sprite(game->door_textures + 2, game->mlx, LIGHT_SIDE_DOOR);
	status += load_sprite(game->door_textures + 3, game->mlx, DARK_SIDE_DOOR);
	status += load_sprite(game->enemy, game->mlx, GUARD_00);
	status += load_sprite(game->enemy + 1, game->mlx, GUARD_01);
	status += load_sprite(game->enemy + 2, game->mlx, GUARD_02);
	status += load_sprite(game->enemy + 3, game->mlx, GUARD_03);
	status += load_sprite(game->enemy + 4, game->mlx, GUARD_04);
	status += load_sprite(game->enemy + 5, game->mlx, GUARD_05);
	status += load_sprite(game->enemy + 6, game->mlx, GUARD_06);
	status += load_sprite(game->enemy + 7, game->mlx, GUARD_07);
	status += load_sprite(game->enemy + 8, game->mlx, GUARD_08);
	return (status);
}

static int	load_all_groups(t_game *game)
{
	int	status;

	status = load_sprite_group(game->weapons[knife], game->mlx, KNIFE_00, 5);
	status += load_sprite_group(game->weapons[pistol], game->mlx, PISTOL_00, 5);
	status += load_sprite_group(game->weapons[machine_gun], game->mlx, \
		MACHINE_GUN_00, 5);
	status += load_sprite_group(game->weapons[submachine_gun], game->mlx, \
		SUBMACHINE_GUN_00, 5);
	status += load_sprite(game->objects + ammo, game->mlx, OBJECT_00);
	status += load_sprite(game->objects + armor, game->mlx, OBJECT_01);
	status += load_sprite(game->objects + barrel, game->mlx, OBJECT_02);
	status += load_sprite(game->objects + bed, game->mlx, OBJECT_03);
	status += load_sprite(game->objects + blood, game->mlx, OBJECT_04);
	status += load_sprite(game->objects + blue_key, game->mlx, OBJECT_05);
	status += load_sprite(game->objects + brass, game->mlx, OBJECT_06);
	status += load_sprite(game->objects + bucket, game->mlx, OBJECT_07);
	status += load_sprite(game->objects + bunch_skeletons, game->mlx, OBJECT_08);
	status += load_sprite(game->objects + cage, game->mlx, OBJECT_09);
	status += load_sprite(game->objects + cage_skeleton, game->mlx, OBJECT_10);
	status += load_sprite(game->objects + crown, game->mlx, OBJECT_11);
	status += load_sprite(game->objects + crucifix, game->mlx, OBJECT_12);
	status += load_sprite(game->objects + cup, game->mlx, OBJECT_13);
	status += load_sprite(game->objects + drinking_fountain, game->mlx, OBJECT_14);
	status += load_sprite(game->objects + empty_pit, game->mlx, OBJECT_15);
	status += load_sprite(game->objects + flag, game->mlx, OBJECT_16);
	status += load_sprite(game->objects + food_01, game->mlx, OBJECT_17);
	status += load_sprite(game->objects + food_02, game->mlx, OBJECT_18);
	status += load_sprite(game->objects + key, game->mlx, OBJECT_19);
	status += load_sprite(game->objects + lamp_01, game->mlx, OBJECT_20);
	status += load_sprite(game->objects + lamp_02, game->mlx, OBJECT_21);
	status += load_sprite(game->objects + lamp_03, game->mlx, OBJECT_22);
	status += load_sprite(game->objects + little_table, game->mlx, OBJECT_23);
	status += load_sprite(game->objects + machine_gun_item, game->mlx, OBJECT_24);
	status += load_sprite(game->objects + medkit, game->mlx, OBJECT_25);
	status += load_sprite(game->objects + oven, game->mlx, OBJECT_26);
	status += load_sprite(game->objects + pillar, game->mlx, OBJECT_27);
	status += load_sprite(game->objects + pitcher, game->mlx, OBJECT_28);
	status += load_sprite(game->objects + pit, game->mlx, OBJECT_29);
	status += load_sprite(game->objects + plant_01, game->mlx, OBJECT_30);
	status += load_sprite(game->objects + plant_02, game->mlx, OBJECT_31);
	status += load_sprite(game->objects + portrait, game->mlx, OBJECT_32);
	status += load_sprite(game->objects + pots_01, game->mlx, OBJECT_33);
	status += load_sprite(game->objects + pots_02, game->mlx, OBJECT_34);
	status += load_sprite(game->objects + puddle, game->mlx, OBJECT_35);
	status += load_sprite(game->objects + roots, game->mlx, OBJECT_36);
	status += load_sprite(game->objects + skeleton_blood, game->mlx, OBJECT_37);
	status += load_sprite(game->objects + skeleton, game->mlx, OBJECT_38);
	status += load_sprite(game->objects + skeleton_lying, game->mlx, OBJECT_39);
	status += load_sprite(game->objects + spears, game->mlx, OBJECT_40);
	status += load_sprite(game->objects + submachine_gun_item, game->mlx, OBJECT_41);
	status += load_sprite(game->objects + table_chairs, game->mlx, OBJECT_42);
	status += load_sprite(game->objects + trash_01, game->mlx, OBJECT_43);
	status += load_sprite(game->objects + trash_02, game->mlx, OBJECT_44);
	status += load_sprite(game->objects + trash_03, game->mlx, OBJECT_45);
	status += load_sprite(game->objects + treasure, game->mlx, OBJECT_46);
	// status += load_sprite(game->objects + pillar, game->mlx, OBJECT_27);
	// status += load_sprite(game->objects + lamp_01, game->mlx, OBJECT_20);
	// status += load_sprite(game->objects + skeleton, game->mlx, OBJECT_38);
	return (status);
}

static int	load_sprite_group(t_image *ptr, void *mlx, char *path, int size)
{
	char	*temp;
	int		errors;
	int		num;
	int		i;

	i = 0;
	errors = 0;
	temp = ft_strdup(path);
	if (!temp)
		return (1);
	num = ft_strlen(path) - 5;
	while (i < size)
	{
		temp[num] = '1' + i;
		errors += load_sprite(ptr + i, mlx, temp);
		i++;
	}
	free(temp);
	return (errors);
}
