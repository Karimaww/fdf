#include "../include/fdf.h"

t_vec2	isometric(t_fdf *fdf, int x, int y, int z)
{
	t_vec2	vec;
	double	angle;
	double	zoom;

	zoom = 30;
	angle = PI / 6;
	x -= fdf->map.sizex / 2;
	y -= fdf->map.sizey / 2;
	x *= zoom;
	y *= zoom;
	z *= zoom * 4 / 10;
	vec.x = cos(angle) * (y - fdf->map.sizey / 2)
		- cos(angle) * (x - fdf->map.sizex / 2);
	vec.y = -z * cos(angle * 2)
		+ sin(angle) * (x - fdf->map.sizex / 2)
		+ sin(angle) * (y - fdf->map.sizey / 2);
	vec.x += fdf->mlx.win_size.x / 2;
	vec.y += fdf->mlx.win_size.y / 2;
	return (vec);
}

void	draw_between(t_fdf *fdf, t_vec2 v1, t_vec2 v2)
{
	t_pixel		p1;
	t_pixel		p2;
	t_vec2		vec;

	vec = isometric(fdf, v1.x, v1.y, fdf->map.map[v1.x][v1.y].z);
	p1.x = vec.x;
	p1.y = vec.y;
	p1.color = fdf->map.map[v1.x][v1.y].color;
	vec = isometric(fdf, v2.x, v2.y, fdf->map.map[v2.x][v2.y].z);
	p2.x = vec.x;
	p2.y = vec.y;
	p2.color = fdf->map.map[v2.x][v2.y].color;
	draw_line(fdf, &p1, &p2);
}