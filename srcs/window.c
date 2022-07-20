/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:19:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:19:28 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	reload_image(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

int	close_window(t_game *game)
{
	printf("Window closed\n");
	end_program(game);
	return (0);
}
