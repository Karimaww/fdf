#include "../include/fdf.h"

t_point	**init_matrix(int sizex, int sizey)
{
	t_point	**mat;
	int		i;

	mat = (t_point **) malloc(sizeof(t_point) * sizey);
	if (!mat)
		return (NULL);
	i = 0;
	while (mat && mat[i])
	{
		mat[i] = (t_point *) malloc(sizeof(t_point) * sizex);
		if (!mat[i])
			return (NULL);
		i++;
	}
	return (mat);
}

t_point	**put_matrix(t_point *lst, int sizex, int sizey)
{
	t_point	**mat;
	t_point	*tmp;
	int		i;
	int		j;

	mat = init_matrix(sizex, sizey);
	i = sizey - 1;
	j = sizex - 1;
	while (mat && mat[i] && i >= 0)
	{
		while (lst && j >= 0)
		{
			mat[i][j] = *lst;
			tmp = lst->next;
			free(lst);
			lst = tmp;
			j--;
		}
		i--;
	}
	return (mat);
}