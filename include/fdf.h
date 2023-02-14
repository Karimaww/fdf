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

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point
{
	int				z;
	int				color;
	struct s_point	*next;
}				t_point;

t_point	**parser(char *file);
t_point	**init_matrix(int sizex, int sizey);
t_point	**put_matrix(t_point *lst, int sizex, int sizey);
int		put_arg(char *line, t_point *lst);
t_point	*put_point_front(char **el, t_point *lst);
t_point	**read_file(int fd);
void	free_mat(t_point **mat, int sizey);
int		hex_to_trgb(char *value);
void	print_mat(t_point **mat);
#endif