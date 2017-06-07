#include "main.h"

void				save_line(t_array_string *arr, t_strp *buff)
{
	if (buff->i > 0)
	{
		add_str_to_array_string(arr, ft_strdup(buff->str));
		ft_bzero(buff->str, buff->i);
		buff->i = 0;
	}
}

t_array_string		*split_line(char *code)
{
	t_strp			*buff;
	t_array_string	*arr;
	int 			i;

	i = 0;
	if ((buff = new_strp(30)) == NULL || (arr = new_array_string(1)) == NULL)
		return (NULL);
	while (code[i] != '\0')
	{
		if (code[i] == ' ' || code[i] == '\t')
			save_line(arr, buff);
		else if (code[i] == ',')
		{
			save_line(arr, buff);
			add_str_to_array_string(arr, ft_strdup(","));
		}
		else if (code[i] == '%')
		{
			save_line(arr, buff);
			add_str_to_array_string(arr, ft_strdup("%"));
		}
		else if (code[i] == ':')
		{
			save_line(arr, buff);
			add_str_to_array_string(arr, ft_strdup(":"));
		}
		else
			put_char_to_strp(buff, code[i]);
		i++;
	}
	if (buff->i > 0)
		add_str_to_array_string(arr, ft_strdup(buff->str));
	del_strp(&buff);
	return (arr);
}
