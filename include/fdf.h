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

# define DEFAULT_COLOR 0x0000FF
# define PI 3.141592654

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}				t_pixel;

typedef struct	s_point
{
	int	z;
	int	color;
}				t_point;

typedef struct	s_map
{
	int		sizex;
	int		sizey;
	t_point	**map;
}				t_map;

typedef struct	s_mlx
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

typedef struct	s_fdf
{
	t_mlx	mlx;
	t_map	map;
}	t_fdf;

/*-----parser utils----*/
t_map	*parser(const char *file);
void	fill_map(t_map *map, char *line, int x, int y);
void	read_map(t_map	*map, int f);
t_map	*parser(const char *file);
t_point	**copy_map(t_point **src, t_point **dest, int x, int y);
int		len_tab(char **tab);
void	free_split(char **str);
void	free_map(t_point **map);

/*-----line utils----*/
t_fdf	*init_fdf(t_map *map);
void	pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_line(t_fdf *fdf, t_pixel p1, t_pixel p2);
void	draw_fdf(t_fdf *fdf);
void	draw_between(t_fdf *fdf, t_vec2 v1, t_vec2 v2);
#endif