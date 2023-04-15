#include "../include/fdf.h"

t_vec2	isometricb(t_fdf *fdf, int x, int y, int z)
{
	t_vec2	vec;
	int		xx;
	int		yy;
	int		zz;

	x -= fdf->map->sizex / 2 + fdf->view.up_down;
	y -= fdf->map->sizey / 2 + fdf->view.up_down;
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	z *= fdf->view.zoom * 4 / 10;
	xx = x;
	yy = y;
	zz = z;
	x = -xx * cos(fdf->view.alpha) + yy * sin(fdf->view.alpha);
	y = xx * sin(fdf->view.alpha) + yy * cos(fdf->view.alpha);
	y = y * cos(fdf->view.beta) - zz * sin(fdf->view.beta);
	vec.x = fdf->mlx.win_size.x / 2 + x;
	vec.y = fdf->mlx.win_size.y / 2 + y;
	return (vec);
}

t_vec2	isometric(t_fdf *fdf, int x, int y, int z)
{
	int		x_p;
	int		y_p;
	t_vec2	v;

	x_p = 0;
	x -= fdf->map->sizex / 2;
	y -= fdf->map->sizey / 2;
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	z *= fdf->view.zoom * 4 / 10 * fdf->view.h;
	x_p += x * cos(fdf->view.theta) * cos(fdf->view.beta);
	x_p -= z * sin(fdf->view.beta);
	x_p -= y * sin(fdf->view.theta) * cos(fdf->view.beta);
	y_p = 0;
	y_p += x * sin(fdf->view.theta) * cos(fdf->view.alpha);
	y_p += y * cos(fdf->view.theta) * cos(fdf->view.alpha);
	y_p += x * cos(fdf->view.theta) * sin(fdf->view.beta)
		* sin(fdf->view.alpha);
	y_p -= y * sin(fdf->view.theta) * sin(fdf->view.beta)
		* sin(fdf->view.alpha);
	y_p += z * cos(fdf->view.beta) * sin(fdf->view.alpha);
	v.x = fdf->mlx.win_size.x / 2 + x_p;
	v.y = fdf->mlx.win_size.y / 2 + y_p;
	return (v);
}
