/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 20:39:49 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/29 16:04:32 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_byte(WINDOW *win, char byte, int position, int attr)
{
	move_to_byte(win, position);
	wattron(win, attr);
	wprintw(win, "%0.2hhx", byte);
	wattroff(win, attr);
	wprintw(win, " ");
}

void		ncurses_live(t_data *data, t_bot *bot)
{
	int		i;

	i = 0;
	if (bot->prev_live != -1)
	{
		while (++i < 5)
			print_byte(data->memory_win, data->map[(bot->prev_live + i +
													MEM_SIZE) % MEM_SIZE],
					(bot->prev_live + i + MEM_SIZE) % MEM_SIZE,
					COLOR_PAIR(bot->number));
	}
	i = 0;
	while (++i < 5)
		print_byte(data->memory_win, data->map[(bot->pc + i + MEM_SIZE) %
											MEM_SIZE], (bot->pc + i +
														MEM_SIZE) % MEM_SIZE,
				COLOR_PAIR(bot->number + 5) | A_BOLD);
	bot->prev_live = bot->pc;
}

void		ncurses_aff(t_data *data, t_bot *bot, int nb_reg)
{
	int		i;
	int		k;
	int		line;

	i = 10;
	while (i >= 0)
	{
		k = -1;
		while (++k < 61)
			data->debug_strs[i + 1][k] = data->debug_strs[i][k];
		i--;
	}
	if ((char)bot->reg[nb_reg] >= 32 && (char)bot->reg[nb_reg] <= 126)
		ft_snprintf(data->debug_strs[0], 61, "Player %d: reg[%d] = %d '%c'",
				bot->number, nb_reg, bot->reg[nb_reg], (char)bot->reg[nb_reg]);
	else
		ft_snprintf(data->debug_strs[0], 61, "Player %d: reg[%d] = %d",
					bot->number, nb_reg, bot->reg[nb_reg]);
	line = 3;
	i = 0;
	while (i < 12)
		mvwprintw(data->debug_win, line++, 4, " %s", data->debug_strs[i++]);
	wrefresh(data->debug_win);
	refresh();
}

void		ncurses_kill_bot_cursor(t_data *data, int position)
{
	chtype	ch;
	int		x;
	int		y;

	move_to_byte(data->memory_win, position);
	getyx(data->memory_win, y, x);
	ch = mvwinch(data->memory_win, y, x);
	print_byte(data->memory_win, data->map[position], position, ch ^ A_REVERSE);
	wrefresh(data->memory_win);
}
