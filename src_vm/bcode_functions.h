#ifndef BCODE_FUNCTIONS_H
# define BCODE_FUNCTIONS_H

# include "vm.h"

int			get_number_from_bcode(const unsigned char *code, int num_size);
int			put_number_to_bcode(t_data *data, int num, int position);

#endif
