#include "../include/fdf.h"

void	get_orig_color(t_fdf *fdf)
{
	if (fdf->theme == &default_theme)
		fdf->theme = &rainbow_theme;
	else if (fdf->theme == &rainbow_theme)
		fdf->theme = &viol_yell_theme;
	else
		fdf->theme = &default_theme;
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_rgb(int color, int i)
{
	if (i == 1)
		return ((color & 0xFF0000) >> 16);
	if (i == 2)
		return ((color & 0xFF00) >> 8);
	return (color & 0xFF);
}

float	get_dist(t_pixel p1, t_pixel p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x)
			+ (p1.y - p2.y) * (p1.y - p2.y)));
}

int	get_color(t_pixel p1, t_pixel p2, float dist)
{
	int				r;
	int				g;
	int				b;
	float			perc;

	perc = 1 - get_dist(p1, p2) / dist;
	r = get_rgb(p1.color, 1) + perc
		* (get_rgb(p2.color, 1) - get_rgb(p1.color, 1));
	g = get_rgb(p1.color, 2) + perc
		* (get_rgb(p2.color, 2) - get_rgb(p1.color, 2));
	b = get_rgb(p1.color, 3) + perc
		* (get_rgb(p2.color, 3) - get_rgb(p1.color, 3));
	return (r << 16 | g << 8 | b);
}
