/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:23:26 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/05 21:54:31 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_textures(char *file_content, int identifier, t_game *game)
{
	int		i;
	int		n;

	i = 2;
	while (ft_isspace(file_content[i]) && file_content[i] && \
			file_content[i] != '\n')
		i++;
	if ((i - 2) == 0)
		error("Invalid Identifier", game);
	n = 0;
	if (game->params.textures[identifier])
		error("Double Identifier", game);
	while (file_content[n] != '\n' && file_content[n])
		n++;
	game->params.textures[identifier] = ft_substr(file_content + 3, 0, n - 3);
	if (!game->params.textures[identifier])
		error("Malloc Failed", game);
	return (n);
}

int	get_env_colors(char *file_content, int identifier, t_game *game)
{
	int		i;
	int		n;
	char	*colors;

	i = 1;
	while (ft_isspace(file_content[i]) && file_content[i] && \
			file_content[i] != '\n')
		i++;
	if ((i - 1) == 0)
		error("Invalid Identifier", game);
	n = 0;
	if (game->params.rgb[identifier])
		error("Double Identifier", game);
	while (file_content[n] != '\n' && file_content[n])
		n++;
	colors = ft_substr(file_content + 1, 0, n);
	if (!colors)
		error("Malloc Failed", game);
	game->params.rgb[identifier] = ft_split(colors, ',');
	ft_free_null((void *)&colors);
	if (!game->params.rgb[identifier])
		error("Malloc Failed", game);
	return (n);
}

int	get_map(char *file_content, t_game *game)
{
	int		lines;
	int		characters;

	game->params.map = ft_split(file_content, '\n');
	if (!game->params.map)
		error("Malloc Failed", game);
	lines = 0;
	characters = 0;
	while (game->params.map[lines])
		characters += ft_strlen(game->params.map[lines++]);
	return ((characters + lines) - 1);
}
