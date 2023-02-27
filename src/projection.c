#include "../include/fdf.h"

t_vec2	isometric(t_fdf *fdf, int x, int y, int z)
{
	t_vec2	vec;
	int	xx;
	int	yy;

	x -= fdf->map->sizex / 2;
	y -= fdf->map->sizey / 2;
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	z *= fdf->view.zoom * 4 / 30 + fdf->view.h;
	xx = x;
	yy = y;
	x = -xx * cos(fdf->view.alpha) + yy * sin(fdf->view.alpha);
	y = xx * sin(fdf->view.alpha) + yy * cos(fdf->view.alpha)
		+ fdf->view.up_down * fdf->view.zoom;
	y = y * cos(fdf->view.beta) - z * sin(fdf->view.beta);
	vec.x = fdf->mlx.win_size.x / 2 + x;
	vec.y = fdf->mlx.win_size.y / 2 + y;
	return (vec);
}

t_vec2	isometric1(t_fdf *fdf, int x, int y, int z)
{
	t_vec2	vec;
	int	zz, normm, qx, qy;
	int radius = PI / 6;

	x -= fdf->map->sizex / 2;
	y -= fdf->map->sizey / 2;
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	z *= fdf->view.zoom * 4 / 30;

	vec.x = x;
	vec.y = y;
	zz = z - fdf->mlx.win_size.y / 10;

	normm = sqrt(vec.x * vec.x + vec.y * vec.y + zz * zz);
	qx = radius * vec.x / normm;
	qy = radius * vec.y / normm;

	vec.x += fdf->mlx.win_size.x / 2 + qx;
	vec.y += fdf->mlx.win_size.y / 2 + qy;
	return (vec);
}

t_vec2	plat(t_fdf *fdf, int x, int y, int z)
{
	t_vec2	rtn;
	double alpha, beta;

	x -= fdf->map->sizex / 2;
	y -= fdf->map->sizey / 2;
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	z *= fdf->view.zoom * 4 / 30;
	alpha = 2 / (fdf->map->sizex * fdf->view.zoom - x);
	beta = - ((fdf->map->sizex * fdf->view.zoom + x) / (fdf->map->sizex * fdf->view.zoom - x));
	rtn.x = alpha * x + beta;
	alpha = 2 / (fdf->map->sizey * fdf->view.zoom - y);
	beta = - ((fdf->map->sizey * fdf->view.zoom + y) / (fdf->map->sizey * fdf->view.zoom - y));
	rtn.y = alpha * y + beta;
	rtn.x = fdf->mlx.win_size.x / 2 + x;;
	rtn.y = fdf->mlx.win_size.y / 2 + y;
	return (rtn);
}


void	draw_between(t_fdf *fdf, t_vec2 v1, t_vec2 v2)
{
	t_pixel		p1;
	t_pixel		p2;
	t_vec2		vec;

	vec = isometric(fdf, v1.x, v1.y, fdf->map->map[v1.x][v1.y].z);
	p1.x = vec.x + fdf->view.left_right * fdf->view.zoom;
	p1.y = vec.y;
	p1.color = fdf->map->map[v1.x][v1.y].color;
	vec = isometric(fdf, v2.x, v2.y, fdf->map->map[v2.x][v2.y].z);
	p2.x = vec.x + fdf->view.left_right * fdf->view.zoom;
	p2.y = vec.y;
	p2.color = fdf->map->map[v2.x][v2.y].color;
	if ((p1.x > 0 && p1.x < fdf->mlx.win_size.x
		&& p1.y > 0 && p1.y < fdf->mlx.win_size.y)
		|| (p2.x > 0 && p2.x < fdf->mlx.win_size.x
		&& p2.y > 0 && p2.y < fdf->mlx.win_size.y))
		draw_line(fdf, p1, p2);
}