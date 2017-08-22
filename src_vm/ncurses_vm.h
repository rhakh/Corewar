#ifndef NCURSES_VM_H
# define NCURSES_VM_H
# define NCURSES_TIMEOUT 100
# include "vm.h"
# include <ncurses.h>

WINDOW			*create_newwin(int height, int width, int starty, int startx);
WINDOW			*create_memory_win(void);
WINDOW			*create_stats_win(void);
WINDOW			*create_debug_win(void);
void			display_memory(t_data *data, WINDOW *win);
void			display_stats(t_data *data, WINDOW *stats_win);
void			display_debug(t_data *data, WINDOW *debug_win);
int 			ncurses_move_cursor(t_data *data, t_bot *bot, int prev);
void			nc_display_arena(t_data *data);
void			nc_terminate(t_data *data);
int				ncurses_change_memory(int start, int len, t_bot *bot, t_data *data);
void			print_byte(WINDOW *win, char *byte, int position, int attr);

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
