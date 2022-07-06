/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:21:25 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/05 18:31:19 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*load_file(int argc, char *argv)
{
	char	*file_content;
	char	*swap;
	char	buffer[501];
	ssize_t	size;
	int		fd;

	fd = check_input(argc, argv);
	if (fd == -1)
		return (NULL);
	file_content = ft_calloc(sizeof(char), 1);
	size = read(fd, buffer, 500);
	while (size > 0)
	{
		buffer[size] = 0;
		swap = ft_strdup(file_content);
		free(file_content);
		file_content = ft_strjoin(swap, buffer);
		free(swap);
		size = read(fd, buffer, 500);
	}
	close(fd);
	if (*file_content == '\0')
		ft_free_null(file_content);
	return (file_content);
}

int	check_input(int argc, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (argc != 2)
		perror("Error\nInvalid number of arguments.");
	else if (fd < 0)
		perror("Error\nCould not open the file.");
	else if (ft_strcmp(".cub", argv + (ft_strlen(argv) - 4)))
		ft_putendl_fd("Error\nInvalid file extension. It must be *.cub", 2);
	else
		return (fd);
	if (fd != -1)
		close(fd);
	return (-1);
}
