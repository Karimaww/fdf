#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_map	*map;
	t_fdf	*fdf;

	if (ac != 2)
		return (write(2, "Error\n", 6), 1);
	map = parser(av[1]);
	if (!map)
		return (write(2, "Error\n", 6), 1);
	fdf = init_fdf(map);
	if (!fdf)
		return (write(2, "Error\n", 6), 1);
	mlx_loop(fdf->mlx.mlx);
	return (0);
}
