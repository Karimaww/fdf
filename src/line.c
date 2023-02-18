#include "../include/fdf.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	printf("we are in my pixel_put\n");
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
		if(p >= 0)  
		{  
			printf("here 1\n");
			pixel_put(&(fdf->mlx), x0, y0, fdf->map.map[x0][y0].color);
			printf("here 2\nx0: %d\n, y0: %d\n", x0, y0);
			y0 = y0 + 1;  
			p = p + 2 * dy - 2 * dx;  
		}  
		else  
		{
			printf("here 3\n, valur of color : %d\n", fdf->map.map[x0][y0].color);
			pixel_put(&(fdf->mlx), x0, y0, fdf->map.map[x0][y0].color);
			printf("here 4\n");
			p = p + 2 * dy;   
		} 
		x0 = x0 + 1;
	}
	printf("Sortie de boucle !\n");
}

void	draw_mat(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < fdf->map.sizey - 1)
	{
		while (j < fdf->map.sizex - 1)
		{
			drawline(fdf, i, j, i, j+1);
			drawline(fdf, i, j, i+1, j);
			j++;
		}
		j = 0;
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
	fdf->mlx.mlx = mlx_init();
	mlx_win = mlx_new_window(fdf->mlx.mlx, 800, 500, "Hello world!");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, 800, 500);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp), &(fdf->mlx.linel),
								&(fdf->mlx.endian));
	drawline(fdf, 5, 5, 10, 10);
	draw_mat(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, mlx_win, fdf->mlx.img, 0, 0);
	mlx_loop(fdf->mlx.mlx);
	return (fdf);
}