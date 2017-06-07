#include "main.h"

t_label_table		*new_label_table(char *name, int offset)
{
	t_label_table	*new;

	if ((new = (t_label_table *)malloc(sizeof(t_label_table))) == NULL)
		return (NULL);
	new->link = ft_strdup(name);
	new->next = NULL;
	new->offset = offset;
	return (new);
}

void				del_label_table(t_label_table **table)
{
	if ((*table)->next != NULL)
		del_label_table((t_label_table **)&((*table)->next));
	if ((*table)->link != NULL)
		free((*table)->link);
	if ((*table) != NULL)
		free(*table);
	*table = NULL;
}

void				print_label_table(t_label_table *table)
{
	t_label_table	*curr;

	curr = table;
	ft_printf("{red}LABEL TABLE{eoc}\n");
	while (curr != NULL)
	{
		ft_printf("{yellow}link: %s, offset: %d{eoc}\n", curr->link, curr->offset);
		curr = curr->next;
	}
}

void				add_label_to_table(t_label_table **table, t_label_table *label)
{
	t_label_table	*curr;

	curr = *table;
	if (*table == NULL)
		*table = label;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = label;
	}
}

t_label_table		*find_label_by_name(t_label_table *table, char *name)
{
	t_label_table	*curr;

	curr = table;
	while (curr)
	{
		if (!ft_strcmp(curr->link, name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}