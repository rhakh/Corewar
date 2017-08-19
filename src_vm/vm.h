#ifndef VM_H
# define VM_H

# include "data.h"
# include "op.h"
# include <fcntl.h>
# include "../new_libft/srcs/libft.h"
# include "args_functions.h"
# include "commands.h"
# include "flags_parser.h"
# include "ncurses_vm.h"

t_bot			*bot_new(int number, t_string *code);
void 			bot_del(t_bot **bot);

WINDOW			*create_memory_win(void);
WINDOW			*create_stats_win(void);
WINDOW			*create_debug_win(void);

// NCURSES
void			move_to_byte(WINDOW *win, int byte);
void			display_memory(t_data *data, WINDOW *win);
void			display_stats(t_data *data, WINDOW *stats_win);
void			display_debug(t_data *data, WINDOW *debug_win);int 			read_bot(t_string *code, char *file_name);
int 			validate_bots(t_data *data);

int 			read_bot(t_string *code, char *file_name);
int 			validate_bots(t_data *data);
void			print_bcode(const char *code, int len);
int				get_number_from_bcode(const unsigned char *code, int num_size);
int				put_number_to_bcode(t_data *data, int num, int position);


#endif
