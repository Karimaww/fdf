#include "../include/fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	draw_between(t_fdf *fdf, t_vec2 v1, t_vec2 v2)
{
	t_pixel		p1;
	t_pixel		p2;
	t_vec2		vec;

	vec = isometric(fdf, v1.x, v1.y, fdf->map->map[v1.x][v1.y].z);
	p1.x = vec.x + fdf->view.left_right * fdf->view.zoom;
	p1.y = vec.y + fdf->view.up_down * fdf->view.zoom;

	fdf->theme(fdf, &p1, v1);
	vec = isometric(fdf, v2.x, v2.y, fdf->map->map[v2.x][v2.y].z);
	p2.x = vec.x + fdf->view.left_right * fdf->view.zoom;
	p2.y = vec.y + fdf->view.up_down * fdf->view.zoom;
	fdf->theme(fdf, &p2, v2);
	if ((p1.x > 0 && p1.x < fdf->mlx.win_size.x
			&& p1.y > 0 && p1.y < fdf->mlx.win_size.y)
		|| (p2.x > 0 && p2.x < fdf->mlx.win_size.x
			&& p2.y > 0 && p2.y < fdf->mlx.win_size.y))
		draw_line(fdf, p1, p2);
}

void	draw_fdf(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->sizey)
	{
		j = 0;
		while (j < fdf->map->sizex)
		{
			if (i != 0)
				draw_between(fdf, (t_vec2){i, j}, (t_vec2){i - 1, j});
			if (j != 0)
				draw_between(fdf, (t_vec2){i, j}, (t_vec2){i, j - 1});
			j++;
		}
		i++;
	}
}
