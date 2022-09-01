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

static void	save_sprites_position(t_game *game);

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
	game->enemies = ft_calloc(sizeof(t_sprites), game->enemies_num);
	if (!game->sprites || !game->enemies)
		error("Malloc Failed", game);
	save_sprites_position(game);
}

static void	save_sprites_position(t_game *game)
{
	int		sprite_counter;
	int		line;
	int		col;

	line = -1;
	sprite_counter = 0;
	while (game->params.map[++line])
	{
		col = -1;
		while (game->params.map[line][++col])
		{
			if (game->params.map[line][col] == 'e')
			{
				game->sprites[sprite_counter].coord.x = (col * TILE_SIZE) + \
					(TILE_SIZE / 2);
				game->sprites[sprite_counter].coord.y = (line * TILE_SIZE) + \
					(TILE_SIZE / 2);
				game->sprites[sprite_counter].is_visible = false;
				game->sprites[sprite_counter].img = game->enemy[0];
				game->params.map[line][col] = '0';
				game->enemies[sprite_counter].enemy_index = sprite_counter;
				sprite_counter++;
			}
		}
	}
}
