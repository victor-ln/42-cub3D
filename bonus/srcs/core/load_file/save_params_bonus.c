/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:02:02 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/05 21:44:49 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_textures(char *file_content, int *identifier);
static int	is_color(char *file_content, int *identifier);

void	save_params(t_game *game)
{
	int		i;
	int		identifier;
	int		elements;

	i = 0;
	elements = 0;
	while (game->file_content[i])
	{
		while (game->file_content[i] == '\n' && game->file_content[i])
			i++;
		if (is_textures(game->file_content + i, &identifier))
			i += get_textures(game->file_content + i, identifier, game);
		else if (is_color(game->file_content + i, &identifier))
			i += get_env_colors(game->file_content + i, identifier, game);
		else if (!game->params.map && elements == 6)
		{
			game->map_cub = game->file_content + i;
			i += get_map(game->file_content + i, game);
		}
		else if (game->file_content[i])
			error ("File configuration is invalid", game);
		if (!game->params.map)
			elements++;
	}
}

static int	is_color(char *file_content, int *identifier)
{
	if (!ft_strncmp(file_content, "F", 1))
		*identifier = ground;
	else if (!ft_strncmp(file_content, "C", 1))
		*identifier = celling;
	else
		return (0);
	return (1);
}

static int	is_textures(char *file_content, int *identifier)
{
	if (!ft_strncmp(file_content, "NO", 2))
		*identifier = NO;
	else if (!ft_strncmp(file_content, "SO", 2))
		*identifier = SO;
	else if (!ft_strncmp(file_content, "WE", 2))
		*identifier = WE;
	else if (!ft_strncmp(file_content, "EA", 2))
		*identifier = EA;
	else
		return (0);
	return (1);
}
