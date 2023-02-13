#include "../include/fdf.h"

void	arg_free(char **arg)
{
	int	i;

	i = 0;
	while(arg[i])
		free(arg[i++]);
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
	point->next = NULL;
	if (el[1])
		point->color = ft_atoi(el[1]);
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
		arg_free(arg);
		return (0);
	}
	while (arg && arg[i])
	{
		el = ft_split(arg[i], ',');
		if (!el)
		{
			free(line);
			arg_free(arg);
			return (0);
		}
		lst = put_point_front(el, lst);
		i++;
	}
	free(line);
	arg_free(arg);
	return (i - 1);
}

t_point	**read_file(int fd)
{
	char	*line;
	int		sizex;
	int		sizey;
	t_point	*lst;

	sizey = 0;
	line = get_next_line(fd);
	lst = NULL;
	while (line)
	{
		sizex = put_arg(line, lst);
		if (!sizex)
			return (NULL);
		line = get_next_line(fd);
		sizey++;
	}
	return (put_matrix(lst, sizex, sizey));
}

int parser(char *file)
{
	int	f;
	f = open(file, O_RDONLY);
	if (!f || !read_file(f))
		return (write(2, "Error\n", 6), 0);
	close(f);
	return (1);
}