#include "../include/fdf.h"

void	ft_close(t_fdf *fdf)
{
	if (fdf->map)
	{
		free_map(fdf->map->map, fdf->map->sizey);
		free(fdf->map);
	}
	if (fdf->mlx.img)
		mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	if (fdf->mlx.win)
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	if (fdf->mlx.mlx)
	{
		mlx_destroy_display(fdf->mlx.mlx);
		free(fdf->mlx.mlx);
	}
	if (fdf)
		free(fdf);
	exit(0);
}

void	clear_screen(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->mlx.win_size.y)
	{
		j = 0;
		while (j < fdf->mlx.win_size.x)
		{
			pixel_put(&fdf->mlx, j, i, 0);
			++j;
		}
		++i;
	}
}

int	ft_key_choose(int key, t_fdf *fdf)
{
	printf("keycode %d\n", key);
	if (key == ESC)
		ft_close(fdf);
	if (key == SPACE)
		get_orig_color(fdf);
	if (key == ARROW_UP || key == ARROW_DOWN)
		hook_zoom(fdf, key);
	if (key == ARROW_LEFT || key == ARROW_RIGHT || key == R || key == T)
		hook_rot(fdf, key);
	if (key == UP || key == DOWN)
		hook_up_down(fdf, key);
	if (key == LEFT || key == RIGHT)
		hook_left_right(fdf, key);
	if (key == HUP || key == HDOWN)
		hook_height(fdf, key);
	clear_screen(fdf);
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	put_info(fdf);
	return (0);
}

int	mouse_hook(t_fdf *fdf)
{
	ft_close(fdf);
	return (0);
}
