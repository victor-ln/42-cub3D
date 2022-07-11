/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:54:37 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/11 18:55:02 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_and_exit(char *msg, t_game *game)
{
	printf("Error\n%s%s\n", msg, strerror(errno));
	if (game)
	{
		ft_free_null(game->file_content);
		ft_free_matrix((void **)game->params.map, 0);
		ft_free_matrix((void **)game->params.textures, 4);
		ft_free_matrix((void **)game->params.rgb, 2);
		ft_free_null(game);
	}
	exit(errno);
}
