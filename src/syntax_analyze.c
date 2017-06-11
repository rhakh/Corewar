#include "main.h"

void		set_labels(t_main *main)
{
	int 	i;

	i = 0;
	while (main->lex_strings[i] != NULL)
	{
		if (main->lex_strings[i]->i > 1)
			if (main->lex_strings[i]->arr[1] != NULL && !strcmp(main->lex_strings[i]->arr[1], ":") && !is_command(main->lex_strings[i]->arr[0]))
				add_label_to_table(&main->table, new_label_table(main->lex_strings[i]->arr[0], -1));
		i++;
	}
}

void		correct_labels(t_main *main)
{
	t_linked_list	*curr;
	t_put_label		*label;

	curr = main->list;
	while (curr)
	{
		label = curr->data;
		if (label)
		{
			*label->arg = find_label_by_name(main->table, label->name)->offset - label->curr_pc;
		}
		curr = curr->next;
	}
}

void		build_bcode(t_main *main)
{
	int 	i;
	t_label_table	*link;

	i = 0;
	while (main->lex_strings[i] != NULL)
	{
		if (main->lex_strings[i]->i >= 2)
		{
			if (1 < main->lex_strings[i]->i && !ft_strcmp(main->lex_strings[i]->arr[1], ":") && !is_command(main->lex_strings[i]->arr[0]))
			{
				link = find_label_by_name(main->table, main->lex_strings[i]->arr[0]);
				link->offset = main->pc;
			}
			create_command(main, main->lex_strings[i]);
		}
		else
		{
			ft_printf("{red}Error:{eoc} {yellow}wrong command or label: {eoc}");
			print_string(main->lex_strings[i]);
			ft_printf("\n");
		}
		print_list_as_put_label(main->list);
		i++;
	}
}

void		syntax_analyze(t_main *main)
{
	set_labels(main);

	build_bcode(main);

	print_label_table(main->table);
	print_list_as_put_label(main->list);

	correct_labels(main);
	print_bcode(main->bcode);
}
