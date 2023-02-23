#include "../include/fdf.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	line_low(t_fdf *fdf, int x0, int y0, int x1, int y1)
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

void	line_high(t_fdf *fdf, int x0, int y0, int x1, int y1)
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

void draw_line(t_fdf *fdf, t_pixel p1, t_pixel p2)  
{
	int x0;
	int y0;
	int x1;
	int y1;

	x0 = p1.x;
	y0 = p1.y;
	x1 = p2.x;
	y1 = p2.y;
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		
		if (x0 > x1)
			line_low(fdf, x1, y1, x0, y0);
		else
			line_low(fdf, x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			line_high(fdf, x1, y1, x0, y0);
		else
			line_high(fdf, x0, y0, x1, y1);
	}
}