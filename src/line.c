#include "../include/fdf.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

t_point	centroid(t_map map)
{
	printf("SIZEY : %d\n", map.sizey);
	printf("SIZEX : %d\n", map.sizex);
	t_point	centroid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	centroid.x = 0;
	centroid.y = 0;
	centroid.y = 0;
	while (i < map.sizey)
	{
		printf("yo\n");
		while (j < map.sizex)
		{
			printf("j : %d\n", j);
			centroid.x += map.map[i][j].x;
			centroid.y += map.map[i][j].y;
			centroid.z += map.map[i][j].z;
			j++;
		}
		j = 0;
		i++;
	}
	centroid.x /= map.sizex * map.sizey;
	centroid.y /= map.sizex * map.sizey;
	centroid.z /= map.sizex * map.sizey;
	return centroid;
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

	i = 50;
	j = 50;
	while (i < 500)
	{
		while (j < 500)
		{
			drawline(fdf, j, i, j + 50, i);
			drawline(fdf, j, i, j, i + 50);
			j += 50;
		}
		j = 50;
		i += 50;
	}
	i = 50;
	while (i < 500)
	{
		drawline(fdf, 500, i, 500, i + 50);
		drawline(fdf, i, 500, i + 50, 500);
		i += 50;
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
	mlx_win = mlx_new_window(fdf->mlx.mlx, 1000, 1000, "Hello world!");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, 1000, 1000);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp), &(fdf->mlx.linel),
								&(fdf->mlx.endian));
/*
	t_point	c = centroid(fdf->map);
	printf("CENTROID x: %d y: %d z: %d", c.x, c.y, c.z);
*/
	draw_mat(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, mlx_win, fdf->mlx.img, 0, 0);
	mlx_loop(fdf->mlx.mlx);
	return (fdf);
}