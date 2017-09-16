#include "main.h"
#include <stdio.h>

t_bcode				*new_bcode(char oper_number, char arg_type[3], int *args)
{
	t_bcode			*new;

	if ((new = (t_bcode *)malloc(sizeof(t_bcode))) != NULL)
	{
		if ((new->oper_number = (char *)malloc(sizeof(char))) == NULL)
			return (NULL);
		if ((new->arg_type = (char *)malloc(sizeof(char) * 3)) == NULL)
			return (NULL);
		if ((new->op_code = (char *)malloc(sizeof(char))) == NULL)
			return (NULL);
	}
	else
		return (NULL);
	*new->oper_number = oper_number;
	new->arg_type[0] = arg_type[0];
	new->arg_type[1] = arg_type[1];
	new->arg_type[2] = arg_type[2];
	new->args = args;
	new->next = NULL;
	*new->op_code = get_op_code(arg_type);
	return (new);
}

void				del_bcode(t_bcode **bcode)
{
	if (bcode == NULL || *bcode == NULL)
		return ;
	if ((*bcode)->next != NULL)
		del_bcode((t_bcode **)&((*bcode)->next));
	if ((*bcode)->oper_number != NULL)
		free((*bcode)->oper_number);
	if ((*bcode)->arg_type != NULL)
		free((*bcode)->arg_type);
	if ((*bcode)->op_code != NULL)
		free((*bcode)->op_code);
	if ((*bcode)->args != NULL)
		free((*bcode)->args);
	if ((*bcode) != NULL)
		free(*bcode);
	*bcode = NULL;
}

void				print_bcode(t_bcode *bcode)
{
	t_bcode	*curr;

	curr = bcode;
	ft_printf("{red}BYTE CODE{eoc}\n");
	ft_printf("{yellow}%s %s %8s %8s %8s{eoc}\n",
			"OPN", "OC", "ARG1", "ARG2", "ARG3");
	while (curr != NULL)
	{
		ft_printf("{yellow}%hh3x %hh2x %8x %8x %8x{eoc}\n", *curr->oper_number,
				*curr->op_code, curr->args[0], curr->args[1], curr->args[2]);
		curr = curr->next;
	}
	ft_printf("\n");
}

void				add_bcode(t_bcode **table, t_bcode *code)
{
	t_bcode	*curr;

	curr = *table;
	if (*table == NULL)
		*table = code;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = code;
	}
}
