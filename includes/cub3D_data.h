/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:59:56 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/06 19:38:33 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DATA_H
# define CUB3D_DATA_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>

enum e_environment{
	celling,
	floor
};

enum e_coords {
	NO,
	SO,
	WE,
	EA
};

typedef struct s_game
{
	t_params	params;
	char		*file_content;
	char		*map_cub;
}	t_game;

typedef struct s_params
{
	char	**map;
	char	*textures[4];
	char	**rgb[2];
	int		environment[2];
}	t_params;

#endif
