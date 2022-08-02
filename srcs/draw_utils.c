/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:45:17 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/01 21:46:25 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rectangle(t_img *image, t_img_properties *properties)
{
	unsigned int		i;
	unsigned int		j;

	j = 0;
	while (j < properties->height)
	{
		i = 0;
		while (i < properties->width)
		{
			draw_pixel(image,
                properties->offset_x + i,
                properties->offset_y + j,
                properties->color
            );
			i++;
		}
		j++;
	}
}

void draw_line(t_img *minimap, t_img_properties *properties)
{
	int		delta_x;
	int		delta_y;
	int		side_length;
	float	x_inc;
	float	y_inc;
	float	current_x;
	float	current_y;
	int		i;

	delta_x = (properties->width - properties->offset_x);
	delta_y = (properties->height - properties->offset_y);
	if (abs(delta_x) >= abs(delta_y))
		side_length = abs(delta_x);
	else
		side_length = abs(delta_y);
	x_inc = delta_x / (float)side_length;
	y_inc = delta_y / (float)side_length;
	current_x = properties->offset_x;
	current_y = properties->offset_y;
	i = 0;
	while (i < side_length)
	{
		draw_pixel(minimap, round(current_x), round(current_y), properties->color);
		current_x += x_inc;
		current_y += y_inc;
		i++;
	}
}

void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	*(unsigned int *)
		((img->data + (x * img->bpp / 8 + y * img->size_line))) = color;
}

unsigned int    get_color(t_img *img, int x, int y)
{
    return ((*(unsigned int *)
            (img->data + (x * img->bpp / 8 + y * img->size_line))));
}