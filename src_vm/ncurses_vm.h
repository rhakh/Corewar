#ifndef NCURSES_VM_H
# define NCURSES_VM_H

# include "vm.h"
# include <ncurses.h>

WINDOW		*create_newwin(int height, int width, int starty, int startx);
int 		ncurses_move_cursor(t_bot *bot, int prev);
void		ft_display_arena(t_data *data);
int			send_to_ncurses(int start, int len, t_bot *bot, t_data *data);

#endif
