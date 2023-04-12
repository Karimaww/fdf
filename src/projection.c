#include "../include/fdf.h"

t_vec2	isometric(t_fdf *fdf, int x, int y, int z)
{
	t_vec2	vec;
	int	xx;
	int	yy;
	int zz;

	//printf("X : %d\n", x);
	//printf("Y : %d\n", y);
	x -= fdf->map->sizex / 2 + fdf->view.up_down;
	y -= fdf->map->sizey / 2 + fdf->view.up_down;
	x *= fdf->view.zoom;
	y *= fdf->view.zoom;
	z *= fdf->view.zoom * 4 / 10;
	// vec.x = cos(PI / 6) * (y - fdf->map->sizey / 2)
	// 	- cos(PI / 6) * (x - fdf->map->sizex / 2);
	// vec.y = -z * cos(PI / 6 * 2)
	// 	+ sin(PI / 6) * (x - fdf->map->sizex / 2)
	// 	+ sin(PI / 6) * (y - fdf->map->sizey / 2);
	
	// xx = vec.x;
	// vec.x = vec.x * cos(fdf->view.beta) - z * sin(fdf->view.beta);
	// vec.y = vec.y * cos(fdf->view.alpha) + xx * sin(fdf->view.alpha) * sin(fdf->view.beta) 
	// 			+ z * sin(fdf->view.alpha) * cos(fdf->view.beta);
	// vec.x = cos(fdf->view.alpha) * cos(fdf->view.beta) * x - sin(fdf->view.alpha) * y + cos(fdf->view.alpha) * sin(fdf->view.beta) * z;
	// vec.y = sin(fdf->view.alpha) * cos(fdf->view.beta) * x + cos(fdf->view.alpha) * y + sin(fdf->view.alpha) * sin(fdf->view.beta) * z;
	//xx = vec.x;
	//yy = vec.y;
	/*AXE z*/
	xx = x;
	yy = y;
	zz = z;
	x = -xx * cos(fdf->view.alpha) + yy * sin(fdf->view.alpha);
	y = xx * sin(fdf->view.alpha) + yy * cos(fdf->view.alpha);
	/*AXE x*/
	y = y * cos(fdf->view.beta) - zz * sin(fdf->view.beta);

	vec.x = fdf->mlx.win_size.x / 2 + x;
	vec.y = fdf->mlx.win_size.y / 2 + y;
	return (vec);
}

void	draw_between(t_fdf *fdf, t_vec2 v1, t_vec2 v2)
{
	t_pixel		p1;
	t_pixel		p2;
	t_vec2		vec;

	vec = isometric(fdf, v1.x, v1.y, fdf->map->map[v1.x][v1.y].z);
	p1.x = vec.x + fdf->view.left_right * fdf->view.zoom;
	p1.y = vec.y;
	if (fdf->map->z_min - fdf->map->z_max == 0)
	{
		p1.color = 255;
		p2.color = 255;
	}
	else
	{
		p1.color = (float)255 * ((float)(fdf->map->map[v1.x][v1.y].z - fdf->map->z_min) / (float)(fdf->map->z_max - fdf->map->z_min));
		p2.color = (float)255 * ((float)(fdf->map->map[v2.x][v2.y].z - fdf->map->z_min) / (float)(fdf->map->z_max - fdf->map->z_min));
	}
	//fdf->map->map[v1.x][v1.y].color;
	vec = isometric(fdf, v2.x, v2.y, fdf->map->map[v2.x][v2.y].z);
	p2.x = vec.x + fdf->view.left_right * fdf->view.zoom;
	p2.y = vec.y;
	
	//fdf->map->map[v2.x][v2.y].color;
	if ((p1.x > 0 && p1.x < fdf->mlx.win_size.x
		&& p1.y > 0 && p1.y < fdf->mlx.win_size.y)
		|| (p2.x > 0 && p2.x < fdf->mlx.win_size.x
		&& p2.y > 0 && p2.y < fdf->mlx.win_size.y))
		draw_line(fdf, p1, p2);
}