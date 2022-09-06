/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:45:17 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/06 17:27:59 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rectangle(t_img *image, t_texture_properties *properties)
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

void	draw_line(t_img *minimap, t_texture_properties *properties)
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
		draw_pixel(minimap, \
			round(current[x]), round(current[y]), properties->color);
		current[x] += increment[x];
		current[y] += increment[y];
		i++;
	}
}

void	draw_sprite(t_img *image, t_img *sprite, int x, int y)
{
	register int	i;
	register int	j;

	j = 0;
	while (j < sprite->height)
	{
		i = 0;
		while (i < sprite->width)
		{
			draw_pixel(image, x + i, y + j, get_color(sprite, i, j));
			i++;
		}
		j++;
	}
}
