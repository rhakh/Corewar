/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 20:33:28 by dtelega           #+#    #+#             */
/*   Updated: 2017/09/10 17:18:35 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <ncurses.h>
#include "vm.h"

static void	ncurses_change_memory_help(t_data *data, t_bot *bot, int start)
{
	int		i;

	i = -1;
	while (++i < 4)
		print_byte(data->memory_win, data->map[(start + i + MEM_SIZE) %
			MEM_SIZE], (start + i + MEM_SIZE)
			% MEM_SIZE, COLOR_PAIR(bot->number) | A_BOLD);
}

int			ncurses_change_memory(int start, t_bot *bot, t_data *data)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	y = 0;
	x = 0;
	if (bot->prev_st != -1)
		while (++i < 4)
		{
			move_to_byte(data->memory_win, (bot->prev_st + i + MEM_SIZE)
						% MEM_SIZE);
			if ((mvwinch(data->memory_win, y, x) & A_BOLD) &&
				(mvwinch(data->memory_win, y, x) & COLOR_PAIR(bot->number)))
				bot->prev_attr = COLOR_PAIR(bot->number);
			print_byte(data->memory_win, data->map[(bot->prev_st + i + MEM_SIZE)
					% MEM_SIZE], (bot->prev_st + i + MEM_SIZE) % MEM_SIZE,
					COLOR_PAIR(bot->number));
		}
	ncurses_change_memory_help(data, bot, start);
	bot->prev_st = start;
	return (0);
}

/*
** Applies move cursor effect. VERY PERFECT ATVICHAY
*/

int			ncurses_move_cursor(t_data *data, t_bot *bot, int prev)
{
	chtype		character;
	int			x;
	int			y;

	wrefresh(data->memory_win);
	move_to_byte(data->memory_win, bot->pc);
	getyx(data->memory_win, y, x);
	character = mvwinch(data->memory_win, y, x);
	if (character & A_REVERSE)
		character = character ^ A_REVERSE;
	(bot->prev_attr == (unsigned int)-1) ?
			(bot->prev_attr = COLOR_PAIR(bot->number)) : 0;
	print_byte(data->memory_win, data->map[prev], prev, bot->prev_attr);
	print_byte(data->memory_win, data->map[bot->pc], bot->pc, character |
			A_REVERSE);
	bot->prev_attr = character;
	return (0);
}

/*
** Moves window cursor to given byte.
*/

void		move_to_byte(WINDOW *win, int byte)
{
	int		size;

	size = ft_sqrt(MEM_SIZE);
	wmove(win, byte / size + 1, byte % size * 2 + byte % size + 1);
}
