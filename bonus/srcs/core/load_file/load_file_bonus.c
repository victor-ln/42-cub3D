/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:21:25 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 20:43:54 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	check_input(int argc, char *argv);

void	load_file(t_game *game, int argc, char *argv)
{
	char	*swap;
	char	buffer[501];
	ssize_t	size;
	int		fd;

	fd = check_input(argc, argv);
	if (fd == -1)
		end_game(game);
	game->file_content = ft_calloc(sizeof(char), 1);
	size = read(fd, buffer, 500);
	while (size > 0)
	{
		buffer[size] = 0;
		swap = ft_strdup(game->file_content);
		free(game->file_content);
		game->file_content = ft_strjoin(swap, buffer);
		free(swap);
		size = read(fd, buffer, 500);
	}
	close(fd);
	if (*game->file_content == '\0')
		error("Empty file", game);
}

static int	check_input(int argc, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (argc != 2)
		printf("Error\nInvalid number of arguments. %s", strerror(errno));
	else if (fd < 0)
		printf("Error\nCould not open the file. %s", strerror(errno));
	else if (ft_strcmp(".cub", argv + (ft_strlen(argv) - 4)))
		printf("Error\nInvalid file extension. It must be *.cub");
	else
		return (fd);
	if (fd != -1)
		close(fd);
	return (-1);
}
