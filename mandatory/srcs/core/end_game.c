/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:31:24 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 21:30:29 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error(char *msg, t_game *game)
{
	printf("Error\n%s.\n%s\n", msg, strerror(errno));
	ft_free_matrix((void **)game->params.map, 0);
	ft_free_matrix((void **)game->params.textures, 4);
	ft_free_matrix((void **)game->params.rgb[0], 0);
	ft_free_matrix((void **)game->params.rgb[1], 0);
	destroy_game(game);
	free_game(game);
	exit(errno);
}

void	end_game(t_game *game)
{
	ft_free_matrix((void **)game->params.map, 0);
	ft_free_matrix((void **)game->params.textures, 4);
	ft_free_matrix((void **)game->params.rgb[0], 0);
	ft_free_matrix((void **)game->params.rgb[1], 0);
	destroy_game(game);
	free_game(game);
	exit(errno);
}

void	free_game(t_game *game)
{
	if (game->file_content != INPUT_ERR)
		ft_free_null((void *)&game->file_content);
	ft_free_null((void *)&game->rays);
}

void	destroy_game(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	destroy_sprites(game->wall_textures, game->mlx, TEXTURES_NUM);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		ft_free_null((void *)&game->mlx);
	}
}

void	destroy_sprites(t_image *images, void *mlx, int x)
{
	int		i;

	i = 0;
	while (i < x)
	{
		if (images[i].img)
			mlx_destroy_image(mlx, images[i].img);
		i++;
	}
}
