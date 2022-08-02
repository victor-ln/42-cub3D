/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:54:37 by afaustin          #+#    #+#             */
/*   Updated: 2022/08/01 21:05:23 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_game(t_game *game);
static void	destroy_game(t_game *game);

void	error(char *msg, t_game *game)
{
	printf("Error\n%s.\n%s\n", msg, strerror(errno));
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
		ft_free_null(game->img_properties);
		ft_free_null(game);
	}
}

static void	destroy_game(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->radar)
		mlx_destroy_image(game->mlx, game->radar);
	if (game->small_radar)
		mlx_destroy_image(game->mlx, game->small_radar);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		ft_free_null(game->mlx);
	}
}
