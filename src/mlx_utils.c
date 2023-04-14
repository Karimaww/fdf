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

int	ft_key_choose(int keycode, t_fdf *fdf)
{
	printf("keycode %d\n", keycode);
	if (keycode == ESC)
		ft_close(fdf);
	if (keycode == SPACE)
		get_orig_color(fdf);
	if (keycode == ARROW_UP || keycode == ARROW_DOWN)
		hook_zoom(fdf, keycode);
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		hook_rot(fdf, keycode);
	if (keycode == UP || keycode == DOWN)
		hook_up_down(fdf, keycode);
	if (keycode == LEFT || keycode == RIGHT)
		hook_left_right(fdf, keycode);
	if (keycode == HUP || keycode == HDOWN)
		hook_height(fdf, keycode);
	clear_screen(fdf);
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	return (0);
}

int	render_next_frame(t_fdf *fdf)
{
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	return (0);
}

int	mouse_hook(t_fdf *fdf)
{
	ft_close(fdf);
	return (0);
}
