#include "../include/fdf.h"

/**Kinda scared to try this ngl**/
void	change_color(t_fdf *fdf)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < fdf->map->sizey)
	{
		while (j < fdf->map->sizex)
		{
			if (fdf->map->map[i][j].color == 0xFFFF)
				fdf->map->map[i][j].color = DEFAULT_COLOR;
			else
				fdf->map->map[i][j].color = 0xFFFF;
			j++;
		}
		j = 0;
		i++;
	}
}

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
		fdf->view.up_down += 1;
	if (keycode == DOWN)
		fdf->view.up_down -= 1;
}

void	hook_left_right(t_fdf *fdf, int keycode)
{
	if (keycode == LEFT)
		fdf->view.left_right -= 1;
	if (keycode == RIGHT)
		fdf->view.left_right += 1;
}