#include "../include/fdf.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

static void		plot(t_mlx *mlx, t_pixel p, double grad)
{
	unsigned int	c;
	unsigned int	shift;

	shift = (int)(0xFF * grad);
	c = (p.color | (shift << 24));
	pixel_put(mlx, p.x, p.y, c);
}

static void		fdf_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

static int		get_pixel_color(t_pixel *p1, t_pixel *p2, int mod)
{
	t_vec2	r;
	t_vec2	g;
	t_vec2	b;
	int		dist;

	dist = p2->x - p1->x;
	r.x = (p1->color & 0xFF0000) >> 16;
	r.y = (p2->color & 0xFF0000) >> 16;
	g.x = (p1->color & 0x00FF00) >> 8;
	g.y = (p2->color & 0x00FF00) >> 8;
	b.x = p1->color & 0x0000FF;
	b.y = p2->color & 0x0000FF;
	r.x += ((double)(r.y - r.x) / dist) * mod;
	g.x += ((double)(g.y - g.x) / dist) * mod;
	b.x += ((double)(b.y - b.x) / dist) * mod;
	return ((r.x << 16) + (g.x << 8) + b.x);
}

double	fpart(double x)
{
	return (x > 0 ? x - (int)x : x - (int)x - 1);
}

static void		drawline(int steep, t_fdf *fdf, t_pixel *p1, t_pixel *p2)
{
	int		color;
	int		x;
	double	y;
	double	grad;

	x = p1->x;
	y = (double)p1->y;
	grad = p2->x - p1->x
		? (double)(p2->y - p1->y) / (double)(p2->x - p1->x) : 1;
	while (x < p2->x)
	{
		color = get_pixel_color(p1, p2, x - p1->x);
		if (steep)
		{
			plot(&fdf->mlx, (t_pixel){(int)y - 1, x, color}, fpart(y));
			plot(&fdf->mlx, (t_pixel){(int)y, x, color}, 1 - fpart(y));
		}
		else
		{
			plot(&fdf->mlx, (t_pixel){x, (int)y - 1, color}, fpart(y));
			plot(&fdf->mlx, (t_pixel){x, (int)y, color}, 1 - fpart(y));
		}
		y += grad;
		++x;
	}
}

void	draw_line(t_fdf *fdf, t_pixel *p1, t_pixel *p2)
{
	int	steep;

	steep = abs(p2->y - p1->y) > abs(p2->x - p1->x);
	if (steep)
	{
		fdf_swap(&p1->x, &p1->y);
		fdf_swap(&p2->x, &p2->y);
	}
	if (p1->x > p2->x)
	{
		fdf_swap(&p1->x, &p2->x);
		fdf_swap(&p1->y, &p2->y);
		fdf_swap(&p1->color, &p2->color);
	}
	drawline(steep, fdf, p1, p2);
}