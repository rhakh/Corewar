#ifndef NCURSES_VM_H
# define NCURSES_VM_H

# include "vm.h"
# include <ncurses.h>

WINDOW		*create_newwin(int height, int width, int starty, int startx);
int 		ncurses_move_cursor(t_bot *bot, int prev);
void		ft_display_arena(t_data *data);
int			send_to_ncurses(int start, int len, t_bot *bot, t_data *data);

WINDOW			*create_memory_win(void);
WINDOW			*create_stats_win(void);
WINDOW			*create_debug_win(void);

// NCURSES
void			move_to_byte(WINDOW *win, int byte);
void			display_memory(t_data *data, WINDOW *win);
void			display_stats(t_data *data, WINDOW *stats_win);
void			display_debug(t_data *data, WINDOW *debug_win);int 			read_bot(t_string *code, char *file_name);
int 			validate_bots(t_data *data);


#endif
