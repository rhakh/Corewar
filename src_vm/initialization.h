/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:47:37 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:47:39 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "vm.h"

void			load_bots_in_memory(t_data *data);
int				init_bots(t_data *data, char *argv[MAX_PLAYERS + 1], int num);
int				infinit_loop(t_data *data);
int				process_bots_commands(t_data *data, int next_command);

#endif
