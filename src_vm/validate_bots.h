/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bots.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:47:54 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:47:55 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_BOTS_H
# define VALIDATE_BOTS_H

# include "vm.h"

int			validate_magic_number(t_bot *bot);
int			validate_bot_size(t_bot *bot);
int			validate_bots(t_data *data);
int			aff_operation(t_data *data, t_bot *bot);
int			run_command(t_data *data, t_bot *bot);

#endif
