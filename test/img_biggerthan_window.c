#include "cub3D.h"

int	main(void)
{
	void	*mlx;
	void	*win;
	void	*img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, STD_WINDOW_WIDTH, STD_WINDOW_HEIGHT, "teste");
	img = mlx_new_image(mlx, STD_WINDOW_WIDTH + 200, STD_WINDOW_HEIGHT + 200);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	return (0);
}