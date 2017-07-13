#include "main.h"

static void			save_line(t_array_string *arr, t_strp *buff, char *devider)
{
	if (buff->i > 0)
	{
		add_str_to_array_string(arr, ft_strdup(buff->str));
		ft_bzero(buff->str, buff->last_size);
		buff->i = 0;
	}
	if (devider != NULL)
		add_str_to_array_string(arr, ft_strdup(devider));
}

static void			devider(char *code, t_strp *buff, t_array_string *arr)
{
	int 			i;

	i = -1;
	while (code[++i] != '\0')
		if (code[i] <= 32)
			save_line(arr, buff, NULL);
		else if (	((code[i] == '%') && (is_printable(code[i - 1]) || is_printable(code[i + 1])))
				 ||	((code[i] == ':') && (is_printable(code[i - 1]) || is_printable(code[i + 1])))	)
			save_line(arr, buff, (code[i] == ':') ? ":" : "%");
		else if (code[i] == ',')
			save_line(arr, buff, ",");
		else if (is_comment(code + i))
			return ;
		else if (code[i] > 32)
			put_char_to_strp(buff, code[i]);
	if (buff->i > 0)
		add_str_to_array_string(arr, ft_strdup(buff->str));
}

t_array_string		*split_line(char *code)
{
	t_strp			*buff;
	t_array_string	*arr;

	if ((buff = new_strp(30)) == NULL || (arr = new_array_string(2)) == NULL)
		return (NULL);
	devider(code, buff, arr);
	del_strp(&buff);
	return (arr);
}
