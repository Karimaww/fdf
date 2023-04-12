#include "../include/fdf.h"


int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}


void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x > data->win_size.x || y > data->win_size.y
		|| x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

static int set_i_d(int *d)
{
	if (*d < 0)
	{
		*d = -(*d);
		return (-1);
	}
	return (1);
}

// tres probablement inutile :D
int	get_color(t_pixel p, t_pixel p1, t_pixel p2)
{
	int	color;

	if (p2.x - p1.x == 0 && p2.y - p1.y == 0)
		color = 1;
	else if (p2.x - p1.x != 0)
		color = ((float)(p.x - p1.x) * (float)(p2.color - p1.color) / (p2.x - p1.x)) + p1.color;
	else
		color = ((float)(p.y - p1.y) * (float)(p2.color - p1.color) / (p2.y - p1.y)) + p1.color;
	if (color < 127)
		return (create_rgb(255, color * 2, 0));
	return (create_rgb(255, 255, color * 2));
}

// added tmp so we don't change the inital values of p1.x and p2.x :DDDD
void	line_low(t_fdf *fdf, t_pixel p1, t_pixel p2, t_pixel tmp)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	yi = set_i_d(&dy);
	d = 2 * dy - dx;
	while (tmp.x < p2.x)
	{
		pixel_put(&(fdf->mlx), tmp.x, tmp.y, get_color(tmp, p1, p2));
		if (d > 0)
		{
			tmp.y += yi;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		tmp.x += 1;
	}
}

void	line_high(t_fdf *fdf, t_pixel p1, t_pixel p2, t_pixel tmp)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	xi = set_i_d(&dx);
	d = 2 * dx - dy;
	while (tmp.y < p2.y)
	{
		pixel_put(&(fdf->mlx), tmp.x, tmp.y, get_color(tmp, p1, p2));
		if (d > 0)
		{
			tmp.x += xi;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		tmp.y += 1;
	}
}

/**
 * reminder: p1.x = x0, p1.y = y0, p2.x = x1, p2.y = y1**/
// tmp takes the values of the first point 
void draw_line(t_fdf *fdf, t_pixel p1, t_pixel p2)  
{
	if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
	{
		
		if (p1.x > p2.x)
			line_low(fdf, (t_pixel){p2.x, p2.y, p2.color}, (t_pixel){p1.x, p1.y, p1.color}, (t_pixel){p2.x, p2.y, p2.color});
		else
			line_low(fdf, (t_pixel){p1.x, p1.y, p1.color}, (t_pixel){p2.x, p2.y, p2.color}, (t_pixel){p1.x, p1.y, p1.color});
	}
	else
	{
		if (p1.y > p2.y)
			line_high(fdf, (t_pixel){p2.x, p2.y, p2.color}, (t_pixel){p1.x, p1.y, p1.color}, (t_pixel){p2.x, p2.y, p2.color});
		else
			line_high(fdf, (t_pixel){p1.x, p1.y, p1.color}, (t_pixel){p2.x, p2.y, p2.color}, (t_pixel){p1.x, p1.y, p1.color});
	}
}