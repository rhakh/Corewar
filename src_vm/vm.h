/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:48:10 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:48:12 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "check_live_bots.h"
# include "validate_bots.h"
# include "bots_functions.h"
# include "bcode_functions.h"
# include "st_functions.h"
# include "ld_functions.h"
# include "pause_time.h"
# include "pc_adder.h"
# include "commands_manager.h"
# include "initialization.h"
# include "usage.h"

int				print_dump(t_data *data);
int				sum_processes(t_data *data);

#endif
