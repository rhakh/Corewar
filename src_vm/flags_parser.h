#ifndef FLAGS_PARSER_H
# define FLAGS_PARSER_H

#include "vm.h"

void		exit_error(t_data *data, int error_code);
void		usage(void);
void		add_wn(t_data *data, int *i, char **argv, int argc);
void		add_player(t_data *data, int *i, char **argv, int argc);
int			parse_flags(t_data *data, int argc, char **argv);

#endif
