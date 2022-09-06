/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:43:30 by afaustin          #+#    #+#             */
/*   Updated: 2022/09/06 19:05:31 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "assets.h"

static void	load_menu_group(t_game *game, char *path, char **file, t_img **img);
static void	save_selection_file_name(char **file_name);
static void	save_options_file_name(char **file_name);
static char	*get_resolution(int resolution);

void	load_menus(t_game *game)
{
	char	*path;
	char	*file[17];

	path = ft_strjoin(OPTION_MENU_PATH, get_resolution(game->menu.resolution));
	save_options_file_name(file);
	load_menu_group(game, path, file, game->options_menu);
	free(path);
	path = ft_strjoin(SELECTION_MENU_PATH, \
		get_resolution(game->menu.resolution));
	save_selection_file_name(file);
	load_menu_group(game, path, file, game->selection_menu);
	free(path);
}

static void	load_menu_group(t_game *game, char *path, char **file, t_img **img)
{
	char	*full_path;
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (file[i] != NULL)
	{
		full_path = ft_strjoin(path, file[i]);
		status += load_sprite(img + i, game->mlx, full_path);
		free(full_path);
		i++;
	}
	if (status)
		error("Could not load menu", game);
}

static char	*get_resolution(int resolution)
{
	if (resolution == BIG)
		return ("1280x720/");
	else if (resolution == MID)
		return ("1024x768/");
	else
		return ("720x480/");
}

static void	save_options_file_name(char **file_name)
{
	file_name[0] = O_MENU_STD_01;
	file_name[1] = O_MENU_MOUSE_01;
	file_name[2] = O_MENU_MOUSE_02;
	file_name[3] = O_MENU_MOUSE_03;
	file_name[4] = O_MENU_RES_01;
	file_name[5] = O_MENU_RES_02;
	file_name[6] = O_MENU_RES_03;
	file_name[7] = O_MENU_MAIN_01;
	file_name[8] = O_MENU_MAIN_02;
	file_name[9] = O_MENU_MAIN_03;
	file_name[10] = O_MENU_MBAR_01;
	file_name[11] = O_MENU_MBAR_02;
	file_name[12] = O_MENU_MBAR_03;
	file_name[13] = O_MENU_RBAR_01;
	file_name[14] = O_MENU_RBAR_02;
	file_name[15] = O_MENU_RBAR_03;
	file_name[16] = 0;
}

static void	save_selection_file_name(char **file_name)
{
	file_name[0] = S_MENU_00;
	file_name[1] = S_MENU_RES_00;
	file_name[2] = S_MENU_RES_01;
	file_name[3] = S_MENU_RES_02;
	file_name[4] = S_MENU_OPT_00;
	file_name[5] = S_MENU_OPT_01;
	file_name[6] = S_MENU_OPT_02;
	file_name[7] = S_MENU_EXIT_00;
	file_name[8] = S_MENU_EXIT_01;
	file_name[9] = S_MENU_EXIT_02;
	file_name[10] = 0;
}
