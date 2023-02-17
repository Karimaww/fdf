#include "../include/fdf.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void drawline(t_fdf *fdf, int x0, int y0, int x1, int y1)  
{  
	int dx;
	int	dy;
	int	p;

	dx = x1 - x0;  
	dy = y1 - y0;   
	p = 2 * dy - dx;  
	while (x0 < x1)  
	{  
		if( p >= 0)  
		{  
			pixel_put(fdf->mlx.img, x0, y0, fdf->map.map[x0][y0].color);
			y0 = y0 + 1;  
			p = p + 2 * dy - 2 * dx;  
		}  
		else  
		{  
			pixel_put(fdf->mlx.img, x0, y0, fdf->map.map[x0][y0].color);
			p = p + 2 * dy;   
		} 
		x0 = x0 + 1;
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
	fdf->mlx.mlx = mlx_init();
	mlx_win = mlx_new_window(fdf->mlx.mlx, 800, 500, "Hello world!");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, 800, 500);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bpp, &fdf->mlx.linel,
								&fdf->mlx.endian);
	drawline(fdf, 0, 0, 1, 0); 
	mlx_put_image_to_window(fdf->mlx.mlx, mlx_win, fdf->mlx.img, 0, 0);
	mlx_loop(fdf->mlx.mlx);
	return (fdf);
}