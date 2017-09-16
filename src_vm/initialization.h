#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "vm.h"

void			load_bots_in_memory(t_data *data);
int				init_bots(t_data *data, char *argv[MAX_PLAYERS + 1], int num);
int				infinit_loop(t_data *data);
int				process_bots_commands(t_data *data, int next_command);

#endif
