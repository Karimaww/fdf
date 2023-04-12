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
			return (free(new_map), NULL);
		i++;
	}
	if (!map)
		return (new_map);
	copy_map(map, new_map, sizex, sizey);
	free_map(map, sizey - 1);
	return (new_map);
}

int	fill_map(t_map *map, char *line, int x, int y)
{
	t_point	point;
	char	**full;
	char	**sep;
	int		i;

	i = 0;
	full = ft_split(line, ' ');
	if (!full)
		return (free_split(full), 1);
	map->map = init_point_map(map->map, x, y);
	while (full && i < x && full[i])
	{
		sep = ft_split(full[i], ',');
		if (!sep)
			return (free_split(sep), 1);
		point.z = ft_atoi(sep[0]);
		if (sep[1])
			point.color = hex_to_trgb(sep[1] + 3);
		else
			point.color = DEFAULT_COLOR;
		map->map[y - 1][i] = point;
		free_split(sep);
		i++;
	}
	free_split(full);
	return (0);
}

int	read_map(t_map	*map, int f)
{
	char	*line;
	char	**tmp;
	int		b;

	line = get_next_line(f);
	if (!line)
		return (EXIT_FAILURE);
	tmp = ft_split(line, ' ');
	if (!tmp)
		return (free(line),EXIT_FAILURE);
	map->sizex = len_tab(tmp);
	map->sizey = 0;
	while (line)
	{
		map->sizey += 1;
		b = fill_map(map, line, map->sizex, map->sizey);
		free(line);
		if (b == 1)
			return (EXIT_FAILURE);
		line = get_next_line(f);
	}
	free_split(tmp);
	return (EXIT_SUCCESS);
}

void	find_z_min_max(t_map *map)
{
	int	min;
	int	max;
	int	x;
	int	y;

	min = map->map[0][0].z;
	max = map->map[0][0].z;
	x = 0;
	y = 0;
	while (y < map->sizey)
	{
		while (x < map->sizex)
		{
			if (map->map[y][x].z < min)
				min = map->map[y][x].z;
			if (map->map[y][x].z > max)
				max = map->map[y][x].z;
			x++;
		}
		x = 0;
		y++;
	}
	map->z_min = min;
	map->z_max = max;
}

t_map	*parser(const char *file)
{
	t_map	*map;
	int		f;

	f = open(file, O_RDONLY);
	if (!f)
		return (write(2, "Error\n", 6), NULL);
	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->sizex = 0;
	map->sizey = 0;
	if (read_map(map, f) == EXIT_FAILURE)
		return (free(map), NULL);
	find_z_min_max(map);
	close(f);
	//print_map_me(map->map, map->sizex, map->sizey);
	return (map);
}