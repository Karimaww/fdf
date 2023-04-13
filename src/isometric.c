#include "../include/fdf.h"

t_vec2	isometric(t_fdf *fdf, int x, int y, int z)
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
