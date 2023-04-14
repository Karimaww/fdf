#include "../include/fdf.h"

void	default_theme(t_fdf *fdf, t_pixel *p, t_vec2 v)
{
	p->color = fdf->map->map[v.x][v.y].color;
}

void	rainbow_theme(t_fdf *fdf, t_pixel *p, t_vec2 v)
{
	float	scale;

	if (fdf->map->z_max == fdf->map->z_min)
		p->color = DEFAULT_COLOR;
	scale = (float)(fdf->map->map[v.x][v.y].z - fdf->map->z_min)
		/ (float)(fdf->map->z_max - fdf->map->z_min);
	if (scale >= 6.0f / 7.0f)
		p->color = create_rgb(185, 66, 245);
	else if (scale >= 5.0f / 7.0f)
		p->color = create_rgb(66, 84, 245);
	else if (scale >= 4.0f / 7.0f)
		p->color = create_rgb(66, 227, 245);
	else if (scale >= 3.0f / 7.0f)
		p->color = create_rgb(92, 245, 66);
	else if (scale >= 2.0f / 7.0f)
		p->color = create_rgb(245, 215, 66);
	else if (scale >= 1.0f / 7.0f)
		p->color = create_rgb(245, 147, 66);
	else
		p->color = create_rgb(232, 49, 21);
}

void	viol_yell_theme(t_fdf *fdf, t_pixel *p, t_vec2 v)
{
	float	scale;

	if (fdf->map->z_max == fdf->map->z_min)
		p->color = DEFAULT_COLOR;
	scale = (float)(fdf->map->map[v.x][v.y].z - fdf->map->z_min)
		/ (float)(fdf->map->z_max - fdf->map->z_min);
	if (scale >= 8.0f / 9.0f)
		p->color = create_rgb(235, 248, 24);
	else if (scale >= 7.0f / 9.0f)
		p->color = create_rgb(255, 214, 0);
	else if (scale >= 6.0f / 9.0f)
		p->color = create_rgb(255, 177, 0);
	else if (scale >= 5.0f / 9.0f)
		p->color = create_rgb(255, 135, 11);
	else if (scale >= 4.0f / 9.0f)
		p->color = create_rgb(255, 86, 57);
	else if (scale >= 3.0f / 9.0f)
		p->color = create_rgb(255, 0, 90);
	else if (scale >= 2.0f / 9.0f)
		p->color = create_rgb(255, 0, 122);
	else if (scale >= 1.0f / 9.0f)
		p->color = create_rgb(245, 0, 155);
	else
		p->color = create_rgb(196, 0, 185);
}

