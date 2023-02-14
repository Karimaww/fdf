#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_point	**mat;
	if (ac != 2)
		return (write(2, "Error\n", 6), 1);
	mat = parser(av[1]);
	if (!mat)
		return (write(2, "Error\n", 6), 1);
	print_mat(mat);
	return (0);
}