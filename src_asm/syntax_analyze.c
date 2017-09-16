#include "main.h"

static void			correct_labels(t_main *main)
{
	t_linked_list	*curr;
	t_label_table	*curr_label;
	t_put_label		*put_label;

	curr = main->list;
	while (curr)
	{
		put_label = curr->data;
		if (put_label)
		{
			curr_label = find_label_by_name(main->table, put_label->name);
			if (curr_label != NULL)
				*put_label->arg = curr_label->offset - put_label->curr_pc;
			else
				print_syntax_error_label(" can't find link with this name ",
										put_label->name, main);
		}
		curr = curr->next;
	}
}

static void			build_bcode(t_main *main)
{
	int				i;
	t_label_table	*link;

	i = 0;
	while (main->lex_strings[i] != NULL)
	{
		if (main->lex_strings[i]->i >= 2)
		{
			if (1 < main->lex_strings[i]->i &&
					!ft_strcmp(main->lex_strings[i]->arr[1], ":")
					&& !is_command(main->lex_strings[i]->arr[0]))
			{
				link = new_label_table(main->lex_strings[i]->arr[0], -1);
				add_label_to_table(&main->table, link);
				link->offset = main->pc;
			}
			create_command(main, main->lex_strings[i]);
		}
		else
			print_syntax_error(" wrong command or label: ",
							main->lex_strings[i], main);
		i++;
	}
}

void				syntax_analyze(t_main *main)
{
	build_bcode(main);
	correct_labels(main);
}
