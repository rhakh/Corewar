#include "main.h"

static int 		calculate_label(t_main *main, char *label_name, int *arg)
{
	t_label_table	*label;

	label = find_label_by_name(main->table, label_name);
	if (label != NULL)
	{
		if (label->offset == -1)
			list_push_back(&main->list, new_put_label(label_name, arg, main->pc));
		else
			return (label->offset - main->pc);
	}
	return (0);
}

int 		get_arg(t_main *main, t_array_string *lex_str, int *i, int *arg)
{
	if (is_number(lex_str->arr[*i]))
		return (ft_atoi(lex_str->arr[*i]));
	else if (lex_str->arr[*i][0] == ':')
	{
		*i += 1;
		if (find_label_by_name(main->table, lex_str->arr[*i]) != NULL)
			return (calculate_label(main, lex_str->arr[*i], arg));
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
			return (calculate_label(main, lex_str->arr[*i], arg));
		else
			print_syntax_error("unknown label in line ", lex_str, main);
	}
	return (ft_atoi(lex_str->arr[*i] + 1));
}
