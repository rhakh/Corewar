#include "string.h"

t_string			*string_new(size_t size)
{
	t_string			*res;

	if ((res = (t_string *)malloc(sizeof(t_string))) == NULL)
		return (NULL);
	if ((res->str = ft_strnew(size)) == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

/*
** 0 - ok, 1 - error
*/
static int				string_realloc(t_string *res, size_t new_size)
{
	char 	*new_str;

	if (res)
	{
		if ((new_str = (char *)malloc(sizeof(char) * (new_size + 1))) == NULL)
			return (1);
		ft_bzero(new_str, (new_size + 1));
		ft_memcpy(new_str, res->str, (size_t )res->len);
		if (res->str)
			free(res->str);
		res->str = new_str;
		return (0);
	}
	return (1);
}

/*
** 0 - ok, 1 - error
*/
int 					string_append(t_string *res, const char *str, size_t len)
{
	size_t 		new_size;

	if (res)
	{
		if (res->len + len + 1 >= res->size)
		{
			new_size = 2 * res->size;
			while (new_size > res->size + len)
				new_size *= 2;
			if (string_realloc(res, new_size))
				return (1);
		}
		ft_memcpy(res->str, str, len);
		res->len += len;
		return (0);
	}
	return (1);
}

/*
** 0 - ok, 1 - error
*/
int 					string_append_c(t_string *res, char c)
{
	size_t 		new_size;

	if (res)
	{
		if (res->len + 2 >= res->size)
		{
			new_size = 2 * res->size;
			while (new_size > res->size + 1)
				new_size *= 2;
			if (string_realloc(res, new_size))
				return (1);
		}
		res->str[res->len] = c ;
		res->len++;
		return (0);
	}
	return (1);
}

void					string_del(t_string **res)
{
	if (res && *res)
	{
		if ((*res)->str)
			free((*res)->str);
		free(*res);
		*res = NULL;
	}
}
