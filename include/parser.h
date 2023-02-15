#ifndef PARSER_H
# define PARSER_H
# include "fdf.h"
# include "colors.h"

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

t_map	*parser(const char *file);
void	fill_map(t_map *map, char *line, int x, int y);
void	read_map(t_map	*map, int f);
t_map	*parser(const char *file);
t_point	**copy_map(t_point **src, t_point **dest, int x, int y);
int		len_tab(char **tab);
void	free_split(char **str);
void	free_map(t_point **map);

#endif