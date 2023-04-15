#include "../include/fdf.h"

void	init_view(t_fdf *fdf)
{
	fdf->view.zoom = 20;
	fdf->view.alpha = 20 * PI / 180;
	fdf->view.beta = PI;
	fdf->view.theta = 85 * PI / 180;
	fdf->view.up_down = 0;
	fdf->view.left_right = 0;
	fdf->view.h = 0.1;
	fdf->view.grad = 0;
}

t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = map;
	fdf->mlx.win_size.x = 1800;
	fdf->mlx.win_size.y = 900;
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, fdf->mlx.win_size.x,
			fdf->mlx.win_size.y, "Our first FDF");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->mlx.win_size.x,
			fdf->mlx.win_size.y);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp),
			&(fdf->mlx.linel), &(fdf->mlx.endian));
	fdf->theme = &default_theme;
	init_view(fdf);
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	mlx_hook(fdf->mlx.win, 17, 1L << 0, mouse_hook, fdf);
	mlx_hook(fdf->mlx.win, 2, 1L << 0, ft_key_choose, fdf);
	return (fdf);
}
