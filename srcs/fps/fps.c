/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:41:04 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/03 17:08:58 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start_time(t_game *game)
{
	game->fps.fps_length = 1000000 / FPS_RATE;
	game->fps.ticks_last_frame = 0;
	game->fps.delta = 0;
	game->fps.frames = 0;
	game->fps.fps_string = 0;
	game->fps.fps_offset_x = game->window_width * 0.9;
	game->fps.fps_offset_y = game->window_height * 0.1;
}

void	count_fps(t_game *game)
{
	while (clock() < (game->fps.ticks_last_frame + game->fps.fps_length))
		continue ;
	game->fps.delta = (clock() - game->fps.ticks_last_frame) / 1000.0f;
	game->fps.ticks_last_frame = clock();
	if (game->fps.delta > 0)
		game->fps.frames = (CLOCKS_PER_SEC / game->fps.delta) / 1000;
	if (game->is_on_the_game)
	{
		free(game->fps.fps_string);
		game->fps.fps_string = ft_itoa(game->fps.frames);
	}
}
