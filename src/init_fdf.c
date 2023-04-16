#include "../include/fdf.h"

void	init_view(t_fdf *fdf)
{
	fdf->view.zoom = 20;
	fdf->view.alpha = 20 * PI / 180;
	fdf->view.beta = PI;
	fdf->view.theta = 85 * PI / 180;
	fdf->view.up_down = 2;
	fdf->view.left_right = -4;
	fdf->view.h = 1.5;
	fdf->view.grad = 0;
}

t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = map;
	fdf->mlx.win_size.x = 1200;
	fdf->mlx.win_size.y = 800;
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, fdf->mlx.win_size.x,
			fdf->mlx.win_size.y, "FDF");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->mlx.win_size.x,
			fdf->mlx.win_size.y);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp),
			&(fdf->mlx.linel), &(fdf->mlx.endian));
	fdf->theme = &default_theme;
	init_view(fdf);
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	mlx_hook(fdf->mlx.win, ON_DESTROY, MKEYPRESS, mouse_hook, fdf);
	mlx_hook(fdf->mlx.win, ON_KEYDOWN, MKEYPRESS, ft_key_choose, fdf);
	return (fdf);
}
