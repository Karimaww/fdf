#include "../include/parser.h"

t_point	**copy_map(t_point **src, t_point **dest, int x, int y)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	if (!src || !dest)
		return (NULL);
	while (src[i] && i < y)
	{
		while (j < x)
		{
			printf("ay\n");
			dest[i][j].z = src[i][j].z;
			dest[i][j].color = src[i][j].color;
			printf("ay\n");
			j++;
		}
		j = 0;
		i++;
		printf("oy\n");
	}
	return (dest);
}

void	free_map(t_point **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	if (map)
		free(map);
}

void	print_map_me(t_point **map, int x, int y)
{
	int i, j;
	i = 0, j=0;

	while (i < y)
	{
		while (j < x)
		{
			printf("map[i][j].z : %d\nmap[i][j].color : %d\n", map[i][j].z,map[i][j].color);
			j++;
		}
		j = 0;
		i++;
	}
	return;
}

t_point **init_point_map(t_point **map, int sizex, int sizey)
{
	int	i;
	int j;
	t_point	**new_map;

	i = 0;
	j = 0;
	new_map = (t_point **) malloc(sizeof(t_point *) * sizey);
	if (!new_map)
		return (NULL);
	while (new_map && i < sizey)
	{
		new_map[i] = (t_point *) malloc(sizeof(t_point) * sizex);
		if (!new_map[i])
			return (NULL);
		while (new_map[i] && j < sizex)
		{
			new_map[i][j].z = 0;
			new_map[i][j].color = 0;
			j++;
		}
		j = 0;
		i++;
	}
	if (map == NULL)
	{
		printf("here??\n");
		new_map = copy_map(map, new_map, sizex, sizey);
		free_map(map);
	}
	printf("here: \n");
	//print_map_me(new_map, sizex, sizey);
	return (new_map);
}

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	fill_map(t_map *map, char *line, int x, int y)
{
	t_point	point;
	char	**full;
	char	**sep;
	int		i;

	i = 0;
	full = ft_split(line, ' ');
	//point = malloc(sizeof(t_point));
	map->map = init_point_map(map->map, x, y);
	while (full && full[i] && i < x)
	{
		sep = ft_split(full[i], ',');
		point.z = ft_atoi(full[0]);
		if (sep[1])
			point.color = hex_to_trgb(sep[1] + 3);
		else
			point.color = 0;
		map->map[y - 1][i] = point;
		i++;
	}
}

void	read_map(t_map	*map, int f)
{
	char	*line;

	line = get_next_line(f);
	map->sizey = 0;
	while (line)
	{
		map->sizex = len_tab(ft_split(line, ' '));
		map->sizey += 1;
		fill_map(map, line, map->sizex, map->sizey);
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
	read_map(map, f);
	close(f);
	return (map);
}