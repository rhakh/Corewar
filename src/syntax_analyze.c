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

void		create_com_line(t_array_string *lex_str, t_bcode **bcode, t_label_table *table, int *pc)
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
	(ft_strcmp(str, "live")) ? 0 : (command_live(lex_str, bcode, table, pc));
	(ft_strcmp(str, "ld")) ? 0 : (command_ld(lex_str, bcode, table, pc));
}

void		build_bcode(t_array_string **lex_strs, t_bcode **bcode, t_label_table *table)
{
	int 	i;
	int 	*pc;

	i = 0;
	if ((pc = (int *)malloc(sizeof(int))) == NULL)
		return ;
	*pc = 0;
	while (lex_strs[i] != NULL)
	{
		lex_strs[i]->glob_pc = pc;
		if (lex_strs[i]->i >= 2)
		{
			if (i < lex_strs[i]->i && !ft_strcmp(lex_strs[i]->arr[1], ":") && !is_command(lex_strs[i]->arr[0]))
				find_label_by_name(table, lex_strs[i]->arr[0])->offset = *pc;
			create_com_line(lex_strs[i], bcode, table, pc);
		}
		else
		{
			ft_printf("{red}Error:{eoc} {yellow}wrong command or label: {eoc}");
			print_string(lex_strs[i]);
			ft_printf("\n");
		}
		i++;
	}
}

void		syntax_analyze(t_array_string **lex_strs)
{
	t_label_table	*table;
	t_bcode			*bcode;

	bcode = NULL;
	table = NULL;
	set_labels(&table, lex_strs);
	build_bcode(lex_strs, &bcode, table);
	print_bcode(bcode);
}
