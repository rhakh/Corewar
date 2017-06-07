#include "main.h"
#include <stdio.h>

t_bcode				*new_bcode(char op, char op_code, int *args)
{
	t_bcode			*new;

	if ((new = (t_bcode *)malloc(sizeof(t_bcode))) != NULL)
	{
		if ((new->op = (char *)malloc(sizeof(char))) == NULL)
			return (NULL);
		if ((new->op_code = (char *)malloc(sizeof(char))) == NULL)
			return (NULL);
		if ((new->args = (int *)malloc(sizeof(int) * 3)) == NULL)
			return (NULL);
	}
	else
		return (NULL);
	*new->op = op;
	*new->op_code = op_code;
	new->args[0] = args[0];
	new->args[1] = args[1];
	new->args[2] = args[2];
	new->next = NULL;
	return (new);
}

void				del_bcode(t_bcode **bcode)
{
	if ((*bcode)->next != NULL)
		del_bcode((t_bcode **)&((*bcode)->next));
	if ((*bcode)->op != NULL)
		free((*bcode)->op);
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
	ft_printf("{yellow}%s %s %8s %8s %8s{eoc}\n", "OP", "OC", "ARG1", "ARG2", "ARG3");
	while (curr != NULL)
	{
		ft_printf("{yellow}%hh2x %hh2x %8x %8x %8x{eoc}\n", *curr->op, *curr->op_code, curr->args[0], curr->args[1], curr->args[2]);
//		printf("%2hhx %2hhx %8x %8x %8x\n", *curr->op, *curr->op_code, curr->args[0], curr->args[1], curr->args[2]);
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
