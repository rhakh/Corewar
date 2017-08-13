//
// Created by Serhii Bondar on 8/13/17.
//

#include <curses.h>
#include "vm.h"

/*
 * Moves window cursor to given byte.
 */
void move_to_byte(WINDOW *win, int byte) {
	int size = ft_sqrt(MEM_SIZE);
	wmove(win, byte / size + 1, byte % size * 2 + byte % size + 1);
	wprintw(win, "ff");
	wrefresh(win);
}

