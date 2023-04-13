#include "../include/fdf.h"

void	get_orig_color(t_fdf *fdf, int keycode)
{
	if (keycode == SPACE)
		fdf->view.grad += 1 % 3;
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_color(t_pixel p, t_pixel p1, t_pixel p2, t_fdf *fdf)
{
	int	color;

	if (fdf->view.grad == 0)
		return (p1.color);
	if (p2.x - p1.x == 0 && p2.y - p1.y == 0)
		color = 1;
	else if (p2.x - p1.x != 0)
		color = (float)((p.x - p1.x) * (p2.color - p1.color)
				/ (p2.x - p1.x)) + p1.color;
	else
		color = (float)((p.y - p1.y) * (p2.color - p1.color)
				/ (p2.y - p1.y)) + p1.color;
	if (color < 127)
		return (create_rgb(255, color * 2, 0));
	return (create_rgb(255, 255, color * 2));
}
