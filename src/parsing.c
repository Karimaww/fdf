#include "../include/fdf.h"

void	arg_free(char **arg)
{
	int	i;

	i = 0;
	while(arg && arg[i])
		free(arg[i++]);
	if (arg)
		free(arg);
	return ;
}

t_point	*put_point_front(char **el, t_point *lst)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
	 	return (NULL);
	point->z = ft_atoi(el[0]);
	point->next = lst;
	if (el[1])
		point->color = hex_to_trgb(el[1] + 3);
	else
		point->color = 0;
	if (!lst)
		lst = point;
	else
	{
		point->next = lst;
		lst = point;
	}
	return (lst);
}

int	put_arg(char *line, t_point *lst)
{
	char	**arg;
	char	**el;
	int		i;

	i = 0;
	arg = ft_split(line, ' ');
	if (!arg)
	{
		printf("ayo\n");
		arg_free(arg);
		return (0);
	}
	while (arg && arg[i])
	{
		el = ft_split(arg[i], ',');
		if (!el)
		{
			printf("here\n");
			free(line);
			arg_free(arg);
			return (0);
		}
		lst = put_point_front(el, lst);
		i++;
	}
	//free(line);
	arg_free(arg);
	return (i);
}

t_point	*init_lst()
{
	t_point *lst;

	lst = (t_point *)malloc(sizeof(t_point));
	if (!lst)
		return (NULL);
	lst->color = 0;
	lst->z = 0;
	lst->next = NULL;
	return (lst);
}

t_point	**read_file(int fd)
{
	char	*line;
	int		sizex;
	int		sizey;
	t_point	*lst;

	sizey = 0;
	line = get_next_line(fd);
	lst = init_lst();
	while (line)
	{
		printf("\nligne 1: %s", line);
		sizex = put_arg(line, lst);
		if (!sizex)
			return (NULL);
		free(line);
		printf("ligne 2: %s\n", line);
		line = get_next_line(fd);
		sizey++;
	}
	printf("sizex: %d\nsizey: %d\n", sizex, sizey);
	return (put_matrix(lst, sizex, sizey));
}

t_point	**parser(char *file)
{
	int		f;
	t_point	**mat;

	f = open(file, O_RDONLY);
	if (!f)
		return (write(2, "Error\n", 6), NULL);
	mat = read_file(f);
	if (!mat)
		return (write(2, "Error\n", 6), NULL);
	close(f);
	return (mat);
}