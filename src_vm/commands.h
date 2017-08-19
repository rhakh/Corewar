#ifndef COMMANDS_H
# define COMMANDS_H

#include "vm.h"

int 		arithmetic_operations(t_bot *bot, char command, int args[3]);
int 		logic_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		st_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		ld_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		run_command(t_data *data, t_bot *bot, char command, char opcode, int args[3]);
int 		execute_command(t_data *data, t_bot *bot);
int 		execute_commands(t_data *data);


#endif