#include "main.h"

int 		get_arg(t_main *main, t_array_string *lex_str, int *i)
{
	if (is_number(lex_str->arr[*i]))
		return (ft_atoi(lex_str->arr[*i]));
	else if (lex_str->arr[*i][0] == ':')
	{
		*i += 1;
		if (find_label_by_name(main->table, lex_str->arr[*i]) != NULL)
			return (find_label_by_name(main->table, lex_str->arr[*i])->offset - main->pc);
		else
			print_syntax_error("unknown label in line ", lex_str, main);
	}
	else if (lex_str->arr[*i][0] == '%')
	{
		*i += 1;
		if (is_number(lex_str->arr[*i]))
			return (ft_atoi(lex_str->arr[*i]));
		*i += 1;
		if (find_label_by_name(main->table, lex_str->arr[*i]) != NULL)
			return (find_label_by_name(main->table, lex_str->arr[*i])->offset - main->pc);
		else
			print_syntax_error("unknown label in line ", lex_str, main);
	}
	return (ft_atoi(lex_str->arr[*i] + 1));
}
