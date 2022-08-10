/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:24:00 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:24:00 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		load_environment(t_game *game);
static void		load_textures(t_game *game);
static void		load_images(t_game *game);
static int		load_sprite(t_img **image, void *mlx, char *path);

void	load_game(t_game *game)
{
	load_environment(game);
	load_images(game);
	load_textures(game);
	load_player(game);
	load_rays(game);
}

static void	load_environment(t_game *game)
{
	game->mlx = mlx_init();
	game->minimap.width = get_max_line_size(game->params.map);
	game->minimap.height = ft_count_vectors((void **)game->params.map);
	if (!game->mlx)
		error("Mlx init failed", game);
	game->window = mlx_new_window(game->mlx, game->window_width, \
		game->window_height, "cub3D");
	if (!game->window)
		error("Could not open a window", game);
	game->texture_prop = malloc(sizeof(t_texture_properties));
	game->wall_prop = malloc(sizeof(t_wall_properties));
	game->ray_prop = malloc(sizeof(t_rays_properties) * 2);
	if (!game->texture_prop || !game->wall_prop || !game->ray_prop)
		error("Malloc Failed", game);
}

static void	load_images(t_game *game)
{
	game->minimap.widthpx = game->minimap.width * TILE_SIZE;
	game->minimap.heightpx = game->minimap.height * TILE_SIZE;
	game->img = mlx_new_image(game->mlx, game->window_width, \
		game->window_height);
	game->minimap.tile_size = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	game->minimap.radars[NORMAL] = mlx_new_image(game->mlx, \
		game->minimap.width * game->minimap.tile_size, \
		game->minimap.height * game->minimap.tile_size \
	);
	game->minimap.minimap_size = NORMAL;
	if ((game->minimap.width * game->minimap.tile_size) > \
			game->window_width * MINIMAP_SCALE_FACTOR || \
		(game->minimap.height * game->minimap.tile_size) > \
			game->window_height * MINIMAP_SCALE_FACTOR)
	{
		game->minimap.radars[BIG] = mlx_new_image(game->mlx, \
			game->window_width * MINIMAP_SCALE_FACTOR, \
			game->window_height * MINIMAP_SCALE_FACTOR \
		);
		game->minimap.minimap_size = BIG;
		if (!game->minimap.radars[BIG])
			error("Could not create images", game);
	}
	if (!game->img || !game->minimap.radars[NORMAL])
		error("Could not create images", game);
}

static void	load_textures(t_game *game)
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
	status += load_sprite(game->crosshair, game->mlx, \
		"./assets/xpm/player/48px/crosshair_green.xpm");
	status += load_sprite(game->crosshair + 1, game->mlx, \
		"./assets/xpm/player/48px/crosshair_red.xpm");
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
