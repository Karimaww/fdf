#include "../include/fdf.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	centroid_z(t_map map)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = 0;
	while (i < map.sizey)
	{
		while (j < map.sizex)
		{
			z += map.map[i][j].z;
			j++;
		}
		j = 0;
		i++;
	}
	z /= map.sizex * map.sizey;
	return z;
}

void	lineLow(t_fdf *fdf, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dy < 0)
	{
		yi = - 1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	while (x0 < x1)
	{
		pixel_put(&(fdf->mlx), x0, y0, 0xFFFFFF);
		if (d > 0)
		{
			y0 += yi;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x0 += 1;
	}
}

void	lineHigh(t_fdf *fdf, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx < 0)
	{
		xi = - 1;
		dx = -dx;
	}
	d = 2 * dx - dy;
	while (y0 < y1)
	{
		pixel_put(&(fdf->mlx), x0, y0, 0xFFFFFF);
		if (d > 0)
		{
			x0 += xi;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		y0 += 1;
	}
}


void drawline(t_fdf *fdf, int x0, int y0, int x1, int y1)  
{  
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		
		if (x0 > x1)
			lineLow(fdf, x1, y1, x0, y0);
		else
			lineLow(fdf, x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			lineHigh(fdf, x1, y1, x0, y0);
		else
			lineHigh(fdf, x0, y0, x1, y1);
	}
}

void	draw_mat(t_fdf *fdf)
{
	int	i;
	int	j;
	double sx, sy;

	sy = 1000/ fdf->map.sizey;
	i = sy;
	sx = 1000/fdf->map.sizex;
	j = sx;
	printf("SX :%f\n", sx);
	while (i < 1000/2)
	{
		while (j < 1000/2)
		{
			drawline(fdf, j, i, j + sx, i);
			drawline(fdf, j, i, j, i + sy);
			j += sx;
		}
		j = sx;
		i += sy;
	}
	i = sy;
	while (i < 1000/2)
	{
		drawline(fdf, i, 1000/2, i + sy, 1000/2);
		i += sy;
	}
	j = sx;
	while (j < 1000/2)
	{
		drawline(fdf, 1000/2, j, 1000/2, j + sx);
		j += sx;
	}
	printf("SY : %f\n", sy);
}

t_fdf	*init_fdf(t_map *map)
{
	void	*mlx_win;
	t_fdf	*fdf;
	//int		centre_z, centre_x, centre_y;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = *map;
	fdf->mlx.mlx = mlx_init();
	mlx_win = mlx_new_window(fdf->mlx.mlx, 1000, 1000, "Hello world!");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, 1000, 1000);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp), &(fdf->mlx.linel),
								&(fdf->mlx.endian));

	// centre_z = centroid_z(fdf->map);
	// centre_x = (fdf->map.sizex + 1) / 2;
	// centre_y = (fdf->map.sizey + 1) / 2;
	// printf("CENTROID z:%d x:%d y:%d\n", centre_z, centre_x, centre_y);

	draw_mat(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, mlx_win, fdf->mlx.img, 0, 0);
	mlx_loop(fdf->mlx.mlx);
	return (fdf);
}