#include "../include/fdf.h"

void	draw_fdf(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.sizey)
	{
		j = 0;
		while (j < fdf->map.sizex)
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

int	ft_close(int keycode, t_fdf *fdf)
{
	// keycode for closing using esc
	if (keycode == ESC)
	//(void)keycode;
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	return (0);
}
/*
int	ft_resize(int button, int x, int y, t_fdf *fdf)
{
	return (0);
}
*/
// will print something when u tap anything
int	key_hook(int keycode, t_fdf *fdf)
{
	(void)keycode;
	(void)fdf;
	printf("Hello from key_hook!\n");
	return (0);
}

// will print something when u tap anything
int	key_hook_change_color(int keycode, t_fdf *fdf)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	// space bar is pressed
	if (keycode == SPACE)
	{
		while (i < fdf->map.sizey)
		{
			while (j < fdf->map.sizex)
			{
				fdf->map.map[i][j].color = 0xFFFF;
				j++;
			}
			j = 0;
			i++;
		}
	}
	return (0);
}
/*
int	render_next_frame(t_fdf *fdf)
{

}*/

t_fdf	*init_fdf(t_map *map)
{
	//void	*mlx_win;
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = *map;
	fdf->mlx.win_size.x = 1280;
	fdf->mlx.win_size.y = 800;
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, fdf->mlx.win_size.x, fdf->mlx.win_size.y, "Our first FDF");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->mlx.win_size.x, fdf->mlx.win_size.y);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp), &(fdf->mlx.linel),
								&(fdf->mlx.endian));
	if (fdf->mlx.mlx && fdf->mlx.win)
	{
		mlx_hook(fdf->mlx.win, 2, 1L<<0, ft_close, fdf);
		// -> BUTTON_PRESS : souris 
		//mlx_hook(fdf->mlx.win, 4, 1L<<2, ft_close, fdf);
	}
	//mlx_key_hook(fdf->mlx.win, key_hook, fdf);
	//mlx_key_hook(fdf->mlx.win, key_hook_change_color, fdf);
	//mlx_loop_hook(fdf->mlx.mlx, render_next_frame, fdf);
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	//clear all the screen in the hook
	//put pixel to black and then put the image back
	mlx_loop(fdf->mlx.mlx);
	return (fdf);
}
