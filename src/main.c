#include "../include/fdf.h"

void	print_map(t_map *map)
{
	int x = 0;
	int y = 0;
	while (y < map->sizey)
	{
		while (x < map->sizex)
		{
			printf("%d ", map->map[y][x].z);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_fdf	*fdf;

	if (ac != 2)
		return (write(2, "Error\n", 6), 1);
	map = parser(av[1]);
	if (!map)
	{
		//free_map(map);
		return (write(2, "Error\n", 6), 1);
	}
	//print_map(map);
	fdf = init_fdf(map);
	mlx_loop(fdf->mlx.mlx);
	return (0);
}