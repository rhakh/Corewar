/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bcode_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:46:55 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:46:56 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BCODE_FUNCTIONS_H
# define BCODE_FUNCTIONS_H

# include "vm.h"

int			get_number_from_bcode(const unsigned char *code, int num_size);
int			put_number_to_bcode(t_data *data, int num, int position);

#endif
