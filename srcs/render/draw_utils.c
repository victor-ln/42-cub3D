/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:45:17 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 17:24:42 by afaustin         ###   ########.fr       */
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

void	draw_line(t_image radar, t_texture_properties *properties)
{
	float	increment[2];
	float	current[2];
	int		side_length;
	int		delta[2];
	int		i;

	delta[x] = (properties->width - properties->offset_x);
	delta[y] = (properties->height - properties->offset_y);
	if (abs(delta[x]) >= abs(delta[y]))
		side_length = abs(delta[x]);
	else
		side_length = abs(delta[y]);
	increment[x] = delta[x] / (float)side_length;
	increment[y] = delta[y] / (float)side_length;
	current[x] = properties->offset_x;
	current[y] = properties->offset_y;
	i = 0;
	while (i < side_length)
	{
		draw_pixel(radar, \
			round(current[x]), round(current[y]), properties->color);
		current[x] += increment[x];
		current[y] += increment[y];
		i++;
	}
}

void	draw_sprite(t_image image, t_image sprite, int x, int y)
{
	register int	i;
	register int	j;

	j = 0;
	while (j < sprite.img->height)
	{
		i = 0;
		while (i < sprite.img->width)
		{
			draw_pixel(image, x + i, y + j, get_color(sprite, i, j));
			i++;
		}
		j++;
	}
}
