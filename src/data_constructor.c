#include "main.h"

void		realloc_data(t_data **src)
{
	t_data	*dst;
	int		i;

	i = 0;
	dst = new_data((*src)->size * 2);
	while (i < (*src)->i)
	{
		dst->arr[i] = (*src)->arr[i];
		i++;
	}
	dst->i = (*src)->i;
	dst->size = (*src)->size * 2;
	del_data(*src);
	*src = dst;
}

void		del_all_data(t_data **data)
{
	int		i;

	i = 0;
	while (i < (*data)->i)
	{
		free((*data)->arr[i]);
		i++;
	}
	del_data((*data));
	*data = NULL;
}

void		del_data(t_data *data)
{
	data->i = 0;
	data->size = 0;
	free(data->arr);
	free(data);
}

t_data		*new_data(size_t size)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		return (NULL);
	if ((data->arr = (char **)malloc(sizeof(char *) * size)) == NULL)
	{
		free(data);
		return (NULL);
	}
	ft_bzero(data->arr, sizeof(char *) * size);
	data->size = size;
	data->i = 0;
	return (data);
}

void		print_data(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->i)
	{
		ft_printf("%s\n", data->arr[i]);
		i++;
	}
}

void		read_data(int fd, t_data **data)
{
	char	*tmp;

	while (get_next_line(fd, &tmp) > 0)
	{
		if ((*data)->i + 1 >= (int)(*data)->size)
			realloc_data(data);
		(*data)->arr[(*data)->i] = tmp;
		(*data)->i++;
	}
	if (!ft_strcmp(tmp, ""))
		free(tmp);
}
