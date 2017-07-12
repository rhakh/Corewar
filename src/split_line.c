#include "main.h"

static void			save_line(t_array_string *arr, t_strp *buff)
{
	if (buff->i > 0)
	{
		add_str_to_array_string(arr, ft_strdup(buff->str));
		ft_bzero(buff->str, buff->i);
		buff->i = 0;
	}
}

static void			devider(char *code, t_strp *buff, t_array_string *arr)
{
	int 			i;

	i = -1;
	while (code[++i] != '\0')
		if (code[i] == ' ' || code[i] == '\t' || code[i] == '\v')
			save_line(arr, buff);
		else if (code[i] == ',')
		{
			save_line(arr, buff);
			add_str_to_array_string(arr, ft_strdup(","));
		}
		else if (	((code[i] == '%') && (is_printable(code[i - 1])
										|| is_printable(code[i + 1])))
				||	((code[i] == ':') && (is_printable(code[i - 1])
										|| is_printable(code[i + 1])))	)
		{
			save_line(arr, buff);
			add_str_to_array_string(arr,
									ft_strdup((code[i] == ':') ? ":" : "%"));
		}
		else if (is_comment(code + i))
			return ;
		else if (ft_strchr(CORRECT_CHARS, code[i]))
			put_char_to_strp(buff, code[i]);
}

t_array_string		*split_line(t_main *main, char *code)
{
	t_strp			*buff;
	t_array_string	*arr;

	if ((buff = new_strp(30)) == NULL || (arr = new_array_string(1)) == NULL)
		return (NULL);
	if (check_bot_params(main->name, main->comment, code))
		return (NULL);
	devider(code, buff, arr);
	if (buff->i > 0)
		add_str_to_array_string(arr, ft_strdup(buff->str));
	del_strp(&buff);
	return (arr);
}
