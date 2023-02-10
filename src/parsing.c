#include "../include/fdf.h"

int	read_file(int fd)
{
	t_point	*list_pt;
	int		sizex;
	int		sizey;
	char	*c;

	list_pt = NULL;
	while(read(fd, c, 1) > 0)
	{
		
	}
}

int parser(char *file)
{
	f = open(file, O_RDONLY);
	if (!f)
		return (write(2, "Error\n", 6), 1);
	read_file(f);
	close(f);
}