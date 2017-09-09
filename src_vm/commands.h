#ifndef COMMANDS_H
# define COMMANDS_H

#include "vm.h"

# define LIVE_LEVEL 1

int 		arithmetic_operations(t_data *data, t_bot *bot);
int 		logic_operations(t_data *data, t_bot *bot);
int 		st_operations(t_data *data, t_bot *bot);
int 		ld_operations(t_data *data, t_bot *bot);
int 		run_command(t_data *data, t_bot *bot);
int 		execute_command(t_data *data, t_bot *bot);
int 		execute_commands(t_data *data);
int 		check_for_live_bots(t_data *data);


int 		first_pause(t_data *data);


#endif