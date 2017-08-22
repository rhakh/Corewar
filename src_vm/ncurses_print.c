#include "vm.h"
//
// Created by Dmytro Telega on 8/19/17.
//

void		print_byte(WINDOW *win, char *byte, int position, int attr) {
	move_to_byte(win, position);
	wattron(win, attr);
	wprintw(win, "%0.2hhx", byte);
	wattroff(win, attr);
	wprintw(win, " ");
}