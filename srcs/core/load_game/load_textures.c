/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:33:40 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/31 18:27:07 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_sprite(t_img **image, void *mlx, char *path);

// static load_objects(t_game *game)
// {
    
// }

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
	status += load_sprite(game->crosshair, game->mlx, GREEN_CROSSHAIR);
	status += load_sprite(game->crosshair + 1, game->mlx, RED_CROSSHAIR);
	status += load_sprite(game->door_textures, game->mlx, LIGHT_FRONT_DOOR);
	status += load_sprite(game->door_textures + 1, game->mlx, DARK_FRONT_DOOR);
	status += load_sprite(game->door_textures + 2, game->mlx, LIGHT_SIDE_DOOR);
	status += load_sprite(game->door_textures + 3, game->mlx, DARK_SIDE_DOOR);
	status += load_sprite(game->weapons[knife], game->mlx, KNIFE_00);
	status += load_sprite(game->weapons[knife] + 1, game->mlx, KNIFE_01);
	status += load_sprite(game->weapons[knife] + 2, game->mlx, KNIFE_02);
	status += load_sprite(game->weapons[knife] + 3, game->mlx, KNIFE_03);
	status += load_sprite(game->weapons[knife] + 4, game->mlx, KNIFE_04);
	status += load_sprite(game->weapons[pistol], game->mlx, PISTOL_00);
	status += load_sprite(game->weapons[pistol] + 1, game->mlx, PISTOL_01);
	status += load_sprite(game->weapons[pistol] + 2, game->mlx, PISTOL_02);
	status += load_sprite(game->weapons[pistol] + 3, game->mlx, PISTOL_03);
	status += load_sprite(game->weapons[pistol] + 4, game->mlx, PISTOL_04);
	status += load_sprite(game->weapons[machine_gun], game->mlx, MACHINE_GUN_00);
	status += load_sprite(game->weapons[machine_gun] + 1, game->mlx, MACHINE_GUN_01);
	status += load_sprite(game->weapons[machine_gun] + 2, game->mlx, MACHINE_GUN_02);
	status += load_sprite(game->weapons[machine_gun] + 3, game->mlx, MACHINE_GUN_03);
	status += load_sprite(game->weapons[machine_gun] + 4, game->mlx, MACHINE_GUN_04);
	status += load_sprite(game->weapons[submachine_gun], game->mlx, SUBMACHINE_GUN_00);
	status += load_sprite(game->weapons[submachine_gun] + 1, game->mlx, SUBMACHINE_GUN_01);
	status += load_sprite(game->weapons[submachine_gun] + 2, game->mlx, SUBMACHINE_GUN_02);
	status += load_sprite(game->weapons[submachine_gun] + 3, game->mlx, SUBMACHINE_GUN_03);
	status += load_sprite(game->weapons[submachine_gun] + 4, game->mlx, SUBMACHINE_GUN_04);
	status += load_sprite(game->enemy, game->mlx, GUARD_00);
	status += load_sprite(game->enemy + 1, game->mlx, GUARD_01);
	status += load_sprite(game->enemy + 2, game->mlx, GUARD_02);
	status += load_sprite(game->enemy + 3, game->mlx, GUARD_03);
	status += load_sprite(game->enemy + 4, game->mlx, GUARD_04);
	status += load_sprite(game->enemy + 5, game->mlx, GUARD_05);
	status += load_sprite(game->enemy + 6, game->mlx, GUARD_06);
	status += load_sprite(game->enemy + 7, game->mlx, GUARD_07);
	status += load_sprite(game->enemy + 8, game->mlx, GUARD_08);
	if (status != EXIT_SUCCESS)
		error("Could not load textures", game);
}

/*
	Loads a xpm file located in path to the image address pointer passed.
*/
static int	load_sprite(t_img **image, void *mlx, char *path)
{
	int		height;
	int		width;

	*(image) = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!*(image))
		return (1);
	(*image)->height = height;
	(*image)->width = width;
	return (0);
}
