#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include "colors.h"
# include "events.h"

# define DEFAULT_COLOR 0xFFFFFF
# define PI 3.141592654

typedef struct s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct s_pixel
{
	int			x;
	int			y;
	int			color;
}				t_pixel;

typedef struct s_point
{
	int	z;
	int	color;
}				t_point;

typedef struct s_map
{
	int		sizex;
	int		sizey;
	int		z_min;
	int		z_max;
	t_point	**map;
}				t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		linel;
	int		endian;
	t_vec2	win_size;
}	t_mlx;

typedef struct s_view
{
	double	zoom;
	double	alpha;
	double	beta;
	double	theta;
	double	up_down;
	double	left_right;
	double	h;
	int		grad;
}	t_view;

typedef struct s_fdf
{
	t_mlx	mlx;
	t_map	*map;
	t_view	view;
	void	(*theme)(struct s_fdf *, t_pixel *, t_vec2);
}	t_fdf;

/*-----parser utils----*/
t_map	*parser(const char *file);
int		fill_map(t_map *map, char *line, int x, int y);
int		read_map(t_map	*map, int f);
t_map	*parser(const char *file);
t_point	**copy_map(t_point **src, t_point **dest, int x, int y);
int		len_tab(char **tab);
void	free_split(char **str);
void	free_map(t_point **map, int sizey);

/*-----line utils----*/
t_fdf	*init_fdf(t_map *map);
void	pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_line(t_fdf *fdf, t_pixel p1, t_pixel p2);
void	draw_fdf(t_fdf *fdf);
void	draw_between(t_fdf *fdf, t_vec2 v1, t_vec2 v2);
t_vec2	isometric(t_fdf *fdf, int x, int y, int z);

int		create_rgb(int r, int g, int b);
void	change_color(t_fdf *fdf);
void	hook_zoom(t_fdf *fdf, int keycode);
void	hook_rot(t_fdf *fdf, int keycode);
void	hook_up_down(t_fdf *fdf, int keycode);
void	hook_left_right(t_fdf *fdf, int keycode);
void	hook_height(t_fdf *fdf, int keycode);
void	get_orig_color(t_fdf *fdf);
int		get_color(t_pixel p1, t_pixel p2, float dist);
float	get_dist(t_pixel p1, t_pixel p2);

/*-----mlx utils-----*/
int		mouse_hook(t_fdf *fdf);
int		render_next_frame(t_fdf *fdf);
int		ft_key_choose(int keycode, t_fdf *fdf);
void	clear_screen(t_fdf *fdf);
void	ft_close(t_fdf *fdf);

/*-----color themes-----*/
void	default_theme(t_fdf *fdf, t_pixel *p, t_vec2 v);
void	rainbow_theme(t_fdf *fdf, t_pixel *p, t_vec2 v);
void	viol_yell_theme(t_fdf *fdf, t_pixel *p, t_vec2 v);
#endif