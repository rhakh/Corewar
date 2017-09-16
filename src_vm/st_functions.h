/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:47:46 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:47:47 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ST_FUNCTIONS_H
# define ST_FUNCTIONS_H

# include "vm.h"

int			st_command(t_data *data, t_bot *bot);
int			sti_command(t_data *data, t_bot *bot);
int			st_operations(t_data *data, t_bot *bot);

#endif
