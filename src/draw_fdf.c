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

t_fdf	*init_fdf(t_map *map)
{
	void	*mlx_win;
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = *map;
	fdf->mlx.win_size.x = 1200;
	fdf->mlx.win_size.y = 800;
	fdf->mlx.mlx = mlx_init();
	mlx_win = mlx_new_window(fdf->mlx.mlx, fdf->mlx.win_size.x, fdf->mlx.win_size.y, "Our first FDF");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, fdf->mlx.win_size.x, fdf->mlx.win_size.y);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp), &(fdf->mlx.linel),
								&(fdf->mlx.endian));

	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, mlx_win, fdf->mlx.img, 0, 0);
	mlx_loop(fdf->mlx.mlx);
	return (fdf);
}