#include "../include/fdf.h"

void	hook_zoom(t_fdf *fdf, int keycode)
{
	if (keycode == ARROW_UP)
		fdf->view.zoom += 0.25;
	if (keycode == ARROW_DOWN && fdf->view.zoom - 0.25 > 0)
		fdf->view.zoom -= 0.25;
}

void	hook_rot(t_fdf *fdf, int keycode)
{
	if (keycode == ARROW_LEFT)
		fdf->view.alpha -= PI / 12;
	if (keycode == ARROW_RIGHT && fdf->view.zoom - 0.25 > 0)
		fdf->view.alpha += PI / 12;
}

void	hook_up_down(t_fdf *fdf, int keycode)
{
	if (keycode == UP)
		fdf->view.up_down -= 1;
	if (keycode == DOWN)
		fdf->view.up_down += 1;
}

void	hook_left_right(t_fdf *fdf, int keycode)
{
	if (keycode == LEFT)
		fdf->view.left_right -= 1;
	if (keycode == RIGHT)
		fdf->view.left_right += 1;
}

void	hook_height(t_fdf *fdf, int keycode)
{
	if (keycode == HUP)
		fdf->view.h -= 0.1;
	if (keycode == HDOWN)
		fdf->view.h += 0.1;
}
