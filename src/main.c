#include "../include/fdf.h"

int	main(int ac, char **av)
{
	if (ac != 2 || !parser(av[1]))
		return (write(2, "Error\n", 6), 1);
	return (0);
}