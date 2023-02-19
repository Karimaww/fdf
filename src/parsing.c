#include "../include/fdf.h"

void	print_map_me(t_point **map, int x, int y)
{
	int i, j;
	i = 0, j=0;

	while (i < y)
	{
		while (j < x)
		{
			printf("%d %d\t", map[i][j].z,map[i][j].color);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
	return;
}

t_point **init_point_map(t_point **map, int sizex, int sizey)
{
	int	i;
	t_point	**new_map;

	i = 0;
	new_map = (t_point **) malloc(sizeof(t_point *) * sizey);
	if (!new_map)
		return (NULL);
	while (new_map && i < sizey)
	{
		new_map[i] = (t_point *) malloc(sizeof(t_point) * sizex);
		if (!new_map[i])
			return (NULL);
		i++;
	}
	if (!map)
		return (new_map);
	copy_map(map, new_map, sizex, sizey);
	free(map);
	return (new_map);
}

void	fill_map(t_map *map, char *line, int x, int y)
{
	t_point	point;
	char	**full;
	char	**sep;
	int		i;

	i = 0;
	full = ft_split(line, ' ');
	map->map = init_point_map(map->map, x, y);
	while (full && i < x && full[i])
	{
		sep = ft_split(full[i], ',');
		point.z = ft_atoi(sep[0]);
		if (sep[1])
			point.color = hex_to_trgb(sep[1] + 3);
		else
			point.color = DEFAULT_COLOR;
		point.y = y - 1;
		point.x = i;
		map->map[y - 1][i] = point;
		i++;
	}
}

void	read_map(t_map	*map, int f)
{
	char	*line;
	char	**tmp;

	line = get_next_line(f);
	tmp = ft_split(line, ' ');
	map->sizex = len_tab(tmp);
	free_split(tmp);
	map->sizey = 0;
	while (line)
	{
		map->sizey += 1;
		fill_map(map, line, map->sizex, map->sizey);
		free(line);
		line = get_next_line(f);
	}
}

t_map	*parser(const char *file)
{
	t_map	*map;
	int		f;

	f = open(file, O_RDONLY);
	if (!f)
		return (write(2, "Error\n", 6), NULL);
	map = (t_map*)malloc(sizeof(t_map));
	map->map = NULL;
	map->sizex = 0;
	map->sizey = 0;
	read_map(map, f);
	close(f);
	print_map_me(map->map, map->sizex, map->sizey);
	return (map);
}