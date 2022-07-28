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

static void	load_player(t_game *game);
static void	save_rotation_angle(t_game *game, char c);
static void	load_environment(t_game *game);
static void	load_rays(t_game *game);

void	load_game(t_game *game)
{
	load_environment(game);
	load_player(game);
	load_rays(game);
}

static void	load_rays(t_game *game)
{
	game->ray_nums = game->width * TILE_SIZE / RAY_STRIP;
	game->rays = malloc(sizeof(t_ray) * game->ray_nums);
	if (!game->rays)
		error("Malloc Failed", game);
}

static void	load_environment(t_game *game)
{
	game->mlx = mlx_init();
	game->width = ft_strlen(game->params.map[0]);
	game->height = ft_count_vectors((void **)game->params.map);
	if (!game->mlx)
		error("Mlx init failed", game);
	game->window = mlx_new_window(game->mlx, game->width * TILE_SIZE, \
		game->height * TILE_SIZE, "cub3D");
	if (!game->window)
		error("Could not open a window", game);
	game->img = mlx_new_image(game->mlx, game->width * TILE_SIZE, \
		game->height * TILE_SIZE);
	game->minimap = mlx_new_image(game->mlx,
		(game->width * TILE_SIZE) * MINIMAP_SCALE_FACTOR,
		(game->height * TILE_SIZE) * MINIMAP_SCALE_FACTOR
	);
	if (!game->img || !game->minimap)
		error("Could not create images", game);
	game->img_properties = malloc(sizeof(t_img_properties));
	if (!game->img_properties)
		error("Malloc Failed", game);
}

static void	save_rotation_angle(t_game *game, char c)
{
	if (c == 'N')
		game->player.coords.angle = M_PI + M_PI_2;
	else if (c == 'S')
		game->player.coords.angle = M_PI_2;
	else if (c == 'W')
		game->player.coords.angle = M_PI;
	else if (c == 'E')
		game->player.coords.angle = 0;
}

static void	load_player(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	game->player.rotation_speed = STD_ROTATION_SPEED * 2;
	while (game->params.map[i])
	{
		j = 0;
		while (game->params.map[i][j])
		{
			if (ft_strchr("NSWE", game->params.map[i][j]))
			{
				save_rotation_angle(game, game->params.map[i][j]);
				game->player.coords.x = j * TILE_SIZE + TILE_SIZE * 0.5;
				game->player.coords.y = i * TILE_SIZE + TILE_SIZE * 0.5;
				game->params.map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
