/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_display_winner.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 20:18:10 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/28 20:24:13 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_winner(t_data *data, t_bot *bot)
{
	wattron(data->stats_win, COLOR_PAIR(bot->number));
	mvwprintw(data->stats_win, 45, 10, "The winner is");
	wattron(data->stats_win, COLOR_PAIR(bot->number + 5) | A_BOLD);
	mvwprintw(data->stats_win, 45, 25, "%s", bot->name);
	wattroff(data->stats_win, COLOR_PAIR(bot->number) |
			COLOR_PAIR(bot->number + 5));
	mvwprintw(data->stats_win, 47, 25, "Type ctrl+C to exit");
	wrefresh(data->stats_win);
	refresh();
}
