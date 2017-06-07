#include "main.h"

t_array_string		**lex_analyze(t_data *code)
{
	t_array_string	**lex_strs;
	int 			i;
	int 			k;

	k = 0;
	i = 0;
	if ((lex_strs = (t_array_string **)malloc(sizeof(t_array_string *) * code->i)) == NULL)
		return (NULL);
	while (i < code->i)
	{
		if (!is_empty_line(code->arr[i]) && code->arr[i][0] != '#')
		{
			lex_strs[k] = split_line(code->arr[i]);
			k++;
		}
		i++;
	}
	lex_strs[k] = NULL; //todo here may be leak
	return (lex_strs);
}

void				print_lex(t_array_string **lex_strs)
{
	int 			i;

	i = 0;
	while (lex_strs[i] != NULL)
	{
		print_array_string(lex_strs[i]);
		i++;
	}
}

void				del_lex_strs(t_array_string ***str)
{
	int 			i;

	i = 0;
	if (*str == NULL)
		return ;
	while ((*str)[i] != NULL)
	{
		del_array_string(&(*str)[i]);
		i++;
	}
	free(*str);
	*str = NULL;
}