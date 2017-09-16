#ifndef COMMANDS_H
# define COMMANDS_H

# include "vm.h"

# define LIVE_LEVEL 1

int			arithmetic_operations(t_bot *bot);
int			logic_operations(t_data *data, t_bot *bot);
int			fork_operations(t_data *data, t_bot *bot);
int			live_operation(t_data *data, t_bot *bot);
int			zjmp_operation(t_bot *bot);

#endif
