/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:27:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/09/07 16:22:27 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	draw_pixel(uint32_t *buffer, uint32_t color)
// {
// 	if (color != TRANSPARENCY)
// 		*buffer = color;
// }

void	draw_pixel(t_img *img, int x, int y, uint32_t color)
{
	if (color != TRANSPARENCY)
		*(img->data + x + y * img->size_line) = color;
}

uint32_t	get_color(t_img *img, int x, int y)
{
	return (*(img->data + x + y * img->size_line));
}

uint32_t	add_shade(uint32_t color, double scale)
{
	int		r;
	int		g;
	int		b;

	if (color == TRANSPARENCY || scale <= SHADE_NUMERATOR)
		return (color);
	scale = SHADE_NUMERATOR / scale;
	r = ((color >> 16) & 0xFF) * scale;
	g = ((color >> 8) & 0xFF) * scale;
	b = (color & 0xFF) * scale;
	return ((r << 16) | (g << 8) | b);
}
