/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 19:23:14 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/28 20:05:18 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_memory(t_data *data, WINDOW *win)
{
	int				i;
	t_bot			*cur_bot;
	t_linked_list	*list;

	i = -1;
	list = data->bots;
	cur_bot = (t_bot *)list->data;
	while (++i < MEM_SIZE)
	{
		if (i % ft_sqrt(MEM_SIZE) == 0)
			ncurses_new_line(win);
		if (cur_bot && i == cur_bot->pc)
		{
			i = ncurses_print_bot_memory(data, cur_bot, i, win);
			list = list->next;
			list ? cur_bot = list->data : 0;
			!list ? cur_bot = NULL : 0;
		}
		else
			print_byte(win, data->map[i], i, COLOR_PAIR(12));
	}
	wrefresh(win);
}

int		ncurses_print_bot_memory(t_data *data, t_bot *cur_bot, int i, WINDOW *w)
{
	int		x;
	int		y;
	int		j;

	print_byte(w, data->map[i], i, COLOR_PAIR(cur_bot->number) | A_REVERSE);
	i++;
	j = 0;
	x = 0;
	y = x;
	while (++j < cur_bot->size)
	{
		print_byte(w, data->map[i], i, COLOR_PAIR(cur_bot->number));
		if (++i % ft_sqrt(MEM_SIZE) == 0 && j + 1 != cur_bot->size)
		{
			getyx(w, y, x);
			wmove(w, y + 1, 1);
		}
	}
	i--;
	return (i);
}

void	ncurses_new_line(WINDOW *win)
{
	int		x;
	int		y;

	x = 0;
	y = x;
	getyx(win, y, x);
	wmove(win, y + 1, 1);
}
