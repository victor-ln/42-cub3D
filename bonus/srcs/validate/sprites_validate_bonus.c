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

#include "cub3D_bonus.h"

static void		save_sprites_params(t_game *game);
static void		save_sprite_position(t_sprites *sprite, int col, int line);
static void		save_object(t_game *game, int sprite_counter, char code);

void	save_sprites(t_game *game)
{
	int		line;

	line = -1;
	game->sprites_num = 0;
	game->enemies_num = 0;
	while (game->params.map[++line]) {
		game->sprites_num += ft_count_charaters(game->params.map[line], "A#$%&'()*+,XYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
		game->enemies_num += ft_count_charaters(game->params.map[line], "A");
	}
	if (!game->sprites_num && !game->enemies_num)
		return ;
	game->sprites = malloc(sizeof(t_sprites) * game->sprites_num);
	game->closest_sprites = malloc(sizeof(int) * game->sprites_num);
	game->visible_sprites = malloc(sizeof(t_sprites) * game->sprites_num);
	game->enemies = ft_calloc(sizeof(t_sprites), game->enemies_num);
	if (!game->sprites || !game->enemies || !game->visible_sprites || \
		!game->closest_sprites)
		error("Malloc Failed", game);
	save_sprites_params(game);
	for (int i = 0; i < game->sprites_num; ++i)
		printf("%d\n", game->sprites[i].enemy_index);
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
			if (is_obj(game->params.map[line][col]))
			{
				save_sprite_position(game->sprites + sprite_counter, col, line);
				save_object(game, sprite_counter, game->params.map[line][col]);
				game->sprites[sprite_counter].is_enemy = false;
				sprite_counter++;
			}
			else if (game->params.map[line][col] == 'A')
			{
				save_sprite_position(game->sprites + sprite_counter, col, line);
				game->sprites[sprite_counter].img = game->enemy[0];
				game->sprites[sprite_counter].enemy_index = enemy_counter;
				game->enemies[enemy_counter++].enemy_index = sprite_counter;
				game->sprites[sprite_counter].is_enemy = true;
				sprite_counter++;
			}
		}
	}
}

int	is_obj(char c)
{
	return ((c >= 88 && c <= 126) || (c >= 35 && c <= 44));
}

static void	save_object(t_game *game, int sprite_counter, char code)
{
	if (code >= 88)
		game->sprites[sprite_counter].img = game->objects[code - 80];
	else
		game->sprites[sprite_counter].img = game->objects[code - 35];
}

static void	save_sprite_position(t_sprites *sprite, int col, int line)
{
	sprite->coord.x = (col * TILE_SIZE) + (TILE_SIZE / 2);
	sprite->coord.y = (line * TILE_SIZE) + (TILE_SIZE / 2);
}
