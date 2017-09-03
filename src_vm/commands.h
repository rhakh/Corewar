#ifndef COMMANDS_H
# define COMMANDS_H

#include "vm.h"

# define ZERO_LEVEL 0
# define LIVE_LEVEL 1
# define CYCLE_LEVEL 2
# define OP_LEVEL 4

int 		arithmetic_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		logic_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		st_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		ld_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		run_command(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		execute_command(t_data *data, t_bot *bot);
int 		execute_commands(t_data *data);
int 		check_for_live_bots(t_data *data);


int 		first_pause(t_data *data);


#endif