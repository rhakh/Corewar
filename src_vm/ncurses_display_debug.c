/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_display_debug.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 19:29:29 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/28 19:29:30 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_debug(t_data *data, WINDOW *debug_win)
{
	int		x;
	int		y;

	wattron(debug_win, COLOR_PAIR(5) | A_REVERSE);
	mvwprintw(debug_win, 1, 28, "DEBUG WIN");
	wattroff(debug_win, COLOR_PAIR(5) | A_REVERSE);
	wrefresh(debug_win);
}
