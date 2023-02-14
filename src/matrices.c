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

	printf("sizex: %d\nsizey: %d\n", sizex, sizey);
	mat = init_matrix(sizex, sizey);
	i = sizey - 1;
	j = sizex - 1;
	tmp = lst;
	while (mat && mat[i] && i >= 0)
	{
		while (tmp && j >= 0)
		{
			printf("This is point z: %d\n", tmp->z);
			mat[i][j] = *tmp;
			tmp = tmp->next;
			j--;
		}
		i--;
	}
	return (mat);
}

void	print_mat(t_point **mat)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 11)
	{

		while (j < 18)
		{
			printf("\t%d", mat[i][j].z);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
}

void	free_mat(t_point **mat, int sizey)
{
	if (mat)
	{
		while (sizey-- > 0)
			free(mat[sizey]);
		free(mat);
	}
}