#include "../include/fdf.h"

void	draw_fdf(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->sizey)
	{
		j = 0;
		while (j < fdf->map->sizex)
		{
			if (i != 0)
				draw_between(fdf, (t_vec2){i, j}, (t_vec2){i - 1, j});
			if (j != 0)
				draw_between(fdf, (t_vec2){i, j}, (t_vec2){i, j - 1});
			j++;
		}
		i++;
	}
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

int	ft_key_choose(int keycode, t_fdf *fdf)
{
	printf("keycode %d\n", keycode);
	if (keycode == ESC)
		ft_close(fdf);
	if (keycode == SPACE)
		change_color(fdf);
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
	//printf("hereee\n");
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	return (0);
}

int	mouse_hook(t_fdf *fdf)
{
	ft_close(fdf);
	return (0);
}

t_fdf	*init_fdf(t_map *map)
{
	//void	*mlx_win;
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = map;
	fdf->mlx.win_size.x = 1280;
	fdf->mlx.win_size.y = 800;
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, fdf->mlx.win_size.x, fdf->mlx.win_size.y, "Our first FDF");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->mlx.win_size.x, fdf->mlx.win_size.y);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp), &(fdf->mlx.linel),
								&(fdf->mlx.endian));
	fdf->view.zoom = 10;
	fdf->view.alpha = atan(sqrt(2));
	fdf->view.beta = PI / 4;
	fdf->view.up_down = 0;
	fdf->view.left_right = 0;
	fdf->view.h = 1;
	//if (fdf->mlx.mlx && fdf->mlx.win)
	//{
		// -> BUTTON_PRESS : souris 
		//mlx_hook(fdf->mlx.win, 4, 1L<<2, ft_close, fdf);
	//}
	//mlx_key_hook(fdf->mlx.win, key_hook, fdf);
	//mlx_key_hook(fdf->mlx.win, key_hook_change_color, fdf);
	/**Basically this will run each time a "hook" is triggered
	 * so for example if you push ESC you will generate a new image**/
	//mlx_loop_hook(fdf->mlx.mlx, render_next_frame, fdf);
	/**mlx_hook and mlx_key_hook are not that different, the only difference is 
	 * that in mlx_hook you specify what keycode your are using**/
	//mlx_hook(fdf->mlx.win, 2, 1L<<0, ft_close, fdf);
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	mlx_hook(fdf->mlx.win, 17,  1L<<0, mouse_hook, fdf);
	mlx_hook(fdf->mlx.win, 2, 1L<<0, ft_key_choose, fdf);
	
	//mlx_key_hook(fdf->mlx.win, key_hook_change_color, fdf);
	//clear all the screen in the hook
	//put pixel to black and then put the image back

	return (fdf);
}
