/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   sprites.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/08/22 21:36:28 by vlima-nu		  #+#	#+#			 */
/*   Updated: 2022/08/22 21:51:38 by vlima-nu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3D.h"

static void		save_sprites_params(t_game *game);
static void		save_sprite_position(t_sprites *sprite, int col, int line);

void	save_sprites(t_game *game)
{
	int		line;

	line = -1;
	game->sprites_num = 0;
	while (game->params.map[++line])
		game->sprites_num += ft_count_char(game->params.map[line], 'e');
	if (!game->sprites_num)
		return ;
	game->enemies_num = game->sprites_num;
	game->sprites = malloc(sizeof(t_sprites) * game->sprites_num);
	game->visible_sprites = malloc(sizeof(t_sprites) * game->sprites_num);
	game->enemies = ft_calloc(sizeof(t_sprites), game->enemies_num);
	if (!game->sprites || !game->enemies || !game->visible_sprites)
		error("Malloc Failed", game);
	save_sprites_params(game);
}

static void	save_sprites_params(t_game *game)
{
	int		sprite_counter;
	int		enemy_counter;
	int		line;
	int		col;

	line = -1;
	sprite_counter = 0;
	enemy_counter = 0;
	while (game->params.map[++line])
	{
		col = -1;
		while (game->params.map[line][++col])
		{
			if (game->params.map[line][col] == 'e')
			{
				save_sprite_position(game->sprites + sprite_counter, col, line);
				game->sprites[sprite_counter].img = game->enemy[0];
				// game->params.map[line][col] = '0';
				game->enemies[enemy_counter++].enemy_index = sprite_counter;
				game->sprites[sprite_counter].is_enemy = true;
				game->sprites[sprite_counter].enemy_index = sprite_counter;
				sprite_counter++;
			}
		}
	}
}

static void	save_sprite_position(t_sprites *sprite, int col, int line)
{
	sprite->coord.x = (col * TILE_SIZE) + (TILE_SIZE / 2);
	sprite->coord.y = (line * TILE_SIZE) + (TILE_SIZE / 2);
}
