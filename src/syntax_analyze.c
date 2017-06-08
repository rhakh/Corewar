#include "main.h"

void		set_labels(t_label_table **table, t_array_string **lex_strs)
{
	int 	i;

	i = 0;
	while (lex_strs[i] != NULL)
	{
		if (lex_strs[i]->i > 1)
			if (lex_strs[i]->arr[1] != NULL && !strcmp(lex_strs[i]->arr[1], ":"))
				add_label_to_table(table, new_label_table(lex_strs[i]->arr[0], 0));
		i++;
	}
}

void		create_com_line(t_main *main, t_array_string *lex_str)
{
	char 	*str;

	str = lex_str->arr[0];
	if (!ft_strcmp(lex_str->arr[1], ":") && !is_command(lex_str->arr[0]))
	{
		if (lex_str->i >= 3)
			str = lex_str->arr[2];
		else
			return;
	}
	(ft_strcmp(str, "live")) ? 0 : (command_live(lex_str, &main->bcode, main->table, &main->pc));
	(ft_strcmp(str, "ld")) ? 0 : (command_ld(main, lex_str, &main->bcode, main->table, &main->pc));
}

void		build_bcode(t_main *main)
{
	int 	i;

	i = 0;
	while (main->lex_strings[i] != NULL)
	{
		if (main->lex_strings[i]->i >= 2)
		{
			if (i < main->lex_strings[i]->i && !ft_strcmp(main->lex_strings[i]->arr[1], ":") && !is_command(main->lex_strings[i]->arr[0]))
				find_label_by_name(main->table, main->lex_strings[i]->arr[0])->offset = main->pc;
			create_com_line(main, main->lex_strings[i]);
		}
		else
		{
			ft_printf("{red}Error:{eoc} {yellow}wrong command or label: {eoc}");
			print_string(main->lex_strings[i]);
			ft_printf("\n");
		}
		i++;
	}
}

void		syntax_analyze(t_main *main)
{
	set_labels(&(main->table), main->lex_strings);
	build_bcode(main);
	print_bcode(main->bcode);
}
