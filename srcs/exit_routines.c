/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:54:37 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/06 17:15:07 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error(char *msg, t_game *game)
{
	printf("Error\n%s%s\n", msg, strerror(errno));
	if (game)
	{
		ft_free_null(file_content);
		ft_free_matrix(game->params.map, 0);
		ft_free_matrix(game->params.textures, 4);
		ft_free_matrix(game->params.colors, 2);
		ft_free_null(game);
	}
	exit(errno);
}
