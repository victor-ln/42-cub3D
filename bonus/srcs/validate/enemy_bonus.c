/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:27:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/14 16:33:26 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	is_enemy_spotted(t_game *game, int i)
{
	t_enemy	*enemy;
	int		enemy_center;
	int		enemy_margin;

	enemy = game->enemies + game->visible_sprites[i].enemy_index;
	enemy_center = \
		(game->texture_prop.offset_x + game->texture_prop.width) >> 1;
	enemy_margin = \
		(game->texture_prop.width - game->texture_prop.offset_x) * 0.15;
	if (game->rays[game->half_width].coord.hipo > \
		game->visible_sprites[i].coord.hipo && !enemy->is_dead)
	{
		if ((game->half_width >= enemy_center - enemy_margin && \
			game->half_width <= enemy_center + enemy_margin))
		{
			game->enemy_spotted = 1;
			return (true);
		}
	}
	return (false);
}

void	kill_enemy(t_game *game, int i)
{
	if (game->player.weapon != knife)
		game->enemies[game->visible_sprites[i].enemy_index].is_dead = true;
	else if (game->visible_sprites[i].coord.hipo <= TILE_SIZE)
		game->enemies[game->visible_sprites[i].enemy_index].is_dead = true;
}
