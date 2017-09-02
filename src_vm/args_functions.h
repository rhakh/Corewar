#ifndef ARGS_FUNCTIONS_H
# define ARGS_FUNCTIONS_H

#include "vm.h"

char 		get_arg_type(char command, char opcode, int i);
int 		check_opcode(char command, char opcode);
int 		get_args(t_data *data, t_bot *bot, char command, char opcode, int args[3]);

#endif
