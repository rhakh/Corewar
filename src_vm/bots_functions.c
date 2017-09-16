/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bots_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbondar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 12:30:11 by sbondar           #+#    #+#             */
/*   Updated: 2017/09/16 12:30:22 by sbondar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bot		*bot_new(int number, t_string *code)
{
	t_bot	*bot;

	if ((bot = (t_bot *)malloc(sizeof(t_bot))) == NULL)
	{
		ft_printf("Can't allocate memory");
		return (NULL);
	}
	ft_bzero(bot, sizeof(t_bot));
	bot->code = code;
	bot->number = number;
	bot->pause_time = 0;
	bot->last_live = 0;
	bot->live_count = 0;
	bot->prev_st = -1;
	bot->prev_live = -1;
	bot->prev_attr = -1;
	return (bot);
}

t_bot		*bot_copy(t_bot *src)
{
	t_bot	*dst;

	if ((dst = bot_new(src->number, NULL)) == NULL)
		return (NULL);
	dst->number = src->number;
	dst->r1_number = src->r1_number;
	dst->pc = src->pc;
	dst->pause_time = src->pause_time;
	dst->prev_live = src->prev_live;
	dst->prev_st = src->prev_st;
	dst->prev_attr = src->prev_attr;
	ft_memcpy(dst->reg, src->reg, (REG_NUMBER + 1) * sizeof(int));
	dst->throw_live = src->throw_live;
	dst->carry = src->carry;
	dst->is_dead = src->is_dead;
	dst->last_live = src->last_live;
	dst->live_count = 0;
	dst->size = src->size;
	dst->start = src->start;
	return (dst);
}

void		bot_del(t_bot **pbot)
{
	t_bot	*bot;

	if (pbot && *pbot)
	{
		bot = *pbot;
		if (bot->name)
			free(bot->name);
		if (bot->comment)
			free(bot->comment);
		if (bot->code)
			string_del(&(bot->code));
		free(bot);
		*pbot = NULL;
	}
}

void		bots_list_del(t_linked_list **head)
{
	t_linked_list		*curr;
	t_linked_list		*next;

	if (head != NULL)
		curr = *head;
	else
		return ;
	if (curr != NULL)
	{
		next = curr;
		while (next != NULL)
		{
			if (curr != NULL)
			{
				next = curr->next;
				bot_del((t_bot **)&(curr->data));
				curr->data = NULL;
				curr->next = NULL;
				free(curr);
				curr = next;
			}
		}
		*head = NULL;
	}
}

int			read_bot(t_string *code, char *file_name)
{
	int		fd;
	int		len;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	ft_bzero(buff, BUFF_SIZE + 1);
	if (fd > 0)
	{
		while ((len = (int)read(fd, buff, BUFF_SIZE)) > 0)
		{
			string_append(code, buff, len);
			ft_bzero(buff, len + 1);
		}
		if (len == 0)
			return (0);
		else
		{
			ft_printf("Read error\n");
			return (1);
		}
	}
	ft_printf("{red}Can't open file '%s'{eoc}\n", file_name);
	return (1);
}
