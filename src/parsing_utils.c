#include "../include/fdf.h"

t_point	**copy_map(t_point **src, t_point **dest, int x, int y)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	if (!src || !dest)
		return (NULL);
	while (src && i < y - 1 && src[i])
	{
		while (dest && j < x && dest[i])
		{
			dest[i][j].z = src[i][j].z;
			dest[i][j].color = src[i][j].color;
			j++;
		}
		j = 0;
		i++;
	}
	return (dest);
}

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	free_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
