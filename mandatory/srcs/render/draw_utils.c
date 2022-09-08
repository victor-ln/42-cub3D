/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:45:17 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 21:28:44 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rectangle(t_image image, t_texture_properties *properties)
{
	int		i;
	int		j;

	j = 0;
	while (j < properties->height)
	{
		i = 0;
		while (i < properties->width)
		{
			draw_pixel(image, \
				properties->offset_x + i, \
				properties->offset_y + j, \
				properties->color \
			);
			i++;
		}
		j++;
	}
}
