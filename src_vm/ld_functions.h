/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:48:29 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:48:30 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LD_FUNCTIONS_H
# define LD_FUNCTIONS_H

# include "vm.h"

int			ld_lld_commands(t_data *data, t_bot *bot);
void		ldi_lldi_commands(t_data *data, t_bot *bot);
int			ld_operations(t_data *data, t_bot *bot);

#endif
