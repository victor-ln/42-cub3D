/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:54:37 by afaustin          #+#    #+#             */
/*   Updated: 2022/08/17 18:34:06 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_game(t_game *game);
static void	destroy_game(t_game *game);
static void	destroy_sprites(t_img **images, void *mlx, int x);

void	error(char *msg, t_game *game)
{
	printf("Error\n%s.\n%s\n", msg, strerror(errno));
	destroy_game(game);
	free_game(game);
	exit(errno);
}

void	end_program(t_game *game)
{
	destroy_game(game);
	free_game(game);
	exit(errno);
}

static void	free_game(t_game *game)
{
	if (game)
	{
		if (game->file_content != INPUT_ERR)
			ft_free_null(game->file_content);
		ft_free_matrix((void **)game->params.map, 0);
		ft_free_matrix((void **)game->params.textures, 4);
		ft_free_matrix((void **)game->params.rgb[0], 0);
		ft_free_matrix((void **)game->params.rgb[1], 0);
		ft_free_null(game->rays);
		ft_free_null(game->texture_prop);
		ft_free_null(game->wall_prop);
		ft_free_null(game->ray_prop);
		ft_free_null(game);
	}
}

static void	destroy_game(t_game *game)
{
	int	i;

	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	destroy_sprites(game->minimap.radars, game->mlx, 2);
	destroy_sprites(game->wall_textures, game->mlx, TEXTURES_NUM);
	destroy_sprites(game->crosshair, game->mlx, 2);
	destroy_sprites(game->door_textures, game->mlx, TEXTURES_NUM);
	destroy_sprites(game->enemy, game->mlx, GUARD_NUM);
	// destroy_sprites(game->objects, game->mlx, OBJECTS_NUM);
	i = 0;
	while (i < WEAPONS_TYPES)
		destroy_sprites(game->weapons[i++], game->mlx, WEAPONS_FRAMES);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		ft_free_null(game->mlx);
	}
}

static void    destroy_sprites(t_img **images, void *mlx, int x)
{
    int        i;

    i = 0;
    if (images)
    {
        while (i < x)
        {
            if (images[i])
                mlx_destroy_image(mlx, images[i]);
            i++;
        }
    }
}