#ifndef FLAGS_PARSER_H
# define FLAGS_PARSER_H

#include "vm.h"

void		exit_error(t_data *data, int error_code);
void		usage(char **argv);
int			parse_flags(t_data *data, int argc, char **argv);

#endif
