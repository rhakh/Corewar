//
// Created by Serhii Bondar on 8/13/17.
//

#include <curses.h>
#include "vm.h"

int			ncurses_change_memory(int start, int len, t_bot *bot, t_data *data) {
	int i = -1;

	while (++i <= len){
		print_byte(data->memory_win, data->map[start + i], start + i, COLOR_PAIR(bot->number) | A_BOLD);
	}
}

/*
 * Applies move cursor effect.
 */
int 		ncurses_move_cursor(t_data *data, t_bot *bot, int prev) {
	print_byte(data->memory_win, data->map[prev], prev, COLOR_PAIR(bot->number));
	print_byte(data->memory_win, data->map[bot->pc], bot->pc, COLOR_PAIR(bot->number) | A_REVERSE);
}

/*
 * Moves window cursor to given byte.
 */
void		move_to_byte(WINDOW *win, int byte) {
	int size = ft_sqrt(MEM_SIZE);
	wmove(win, byte / size + 1, byte % size * 2 + byte % size + 1);
}
