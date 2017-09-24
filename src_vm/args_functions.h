/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:14:28 by dtelega           #+#    #+#             */
/*   Updated: 2017/09/13 19:14:30 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_FUNCTIONS_H
# define ARGS_FUNCTIONS_H

# include "vm.h"

char		get_arg_type(char command, char opcode, int i);
int			check_opcode(char command, char opcode);
int			get_args(t_data *data, t_bot *bot);

#endif
