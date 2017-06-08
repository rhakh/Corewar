#include "main.h"

t_array_string	*new_array_string(size_t size)
{
	t_array_string	*arr;

	if ((arr = (t_array_string *)malloc(sizeof(t_array_string))) == NULL)
		return (NULL);
	if ((arr->arr = (char **) malloc(sizeof(char *) * size)) == NULL)
	{
		free(arr);
		return (NULL);
	}
	arr->i = 0;
	ft_bzero(arr->arr, sizeof(char *) * size);
	arr->size = size;
	return (arr);
}

int			realloc_array_string(t_array_string **arr)
{
	char	**new;
	int 	i;

	i = 0;
	if ((new = (char **)malloc(sizeof(char *) * (*arr)->size * 2)) == NULL)
		return (0);
	while (i < (*arr)->i)
	{
		new[i] = (*arr)->arr[i];
		i++;
	}
	free((*arr)->arr);
	(*arr)->arr = new;
	(*arr)->size *= 2;
	return (1);
}

void			del_array_string(t_array_string **arr)
{
	int		i;

	i = 0;
	if (arr != NULL)
	{
		while (i < (*arr)->i)
		{
			ft_strdel(&((*arr)->arr[i]));
			i++;
		}
		free((*arr)->arr);
		(*arr)->arr = NULL;
		free(*arr);
		*arr = NULL;
	}
}

int 			add_str_to_array_string(t_array_string *arr, char *str)
{
	if ((arr)->i + 1 >= (int)(arr)->size)
		realloc_array_string(&arr);
	if ((arr) == NULL)
		return (0);
	(arr)->arr[(arr)->i] = str;
	(arr)->i++;
	return (1);
}

void 			print_array_string(t_array_string *arr)
{
	int i;

	i = 0;
	if (arr != NULL)
	{
		ft_printf("Array_string = {\n");
		while (i < arr->i)
		{
			ft_printf("[%d] = %s\n", i, arr->arr[i]);
			i++;
		}
		ft_printf("}\n");
	}
}

void			print_string(t_array_string *arr)
{
	int 		i;

	i = 0;
	if (arr != NULL)
	{
		while (i < arr->i)
		{
			ft_printf("%s ", arr->arr[i]);
			i++;
		}
	}
}