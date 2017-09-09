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
# include "sdl_vm.h"

t_bot			*bot_new(int number, t_string *code);
t_bot			*bot_copy(t_bot *src);
void 			bot_del(t_bot **bot);
int 			read_bot(t_string *code, char *file_name);
int 			validate_bots(t_data *data);
int				get_number_from_bcode(const unsigned char *code, int num_size);
int				put_number_to_bcode(t_data *data, int num, int position);
int				sum_processes(t_data *data);

#endif
