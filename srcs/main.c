/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:39:55 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/07/03 19:13:41 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(void)
{
	void	*mlx;
	void	*win;

	(void)win;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "teste");
	mlx_loop(mlx);

	return (0);
}