/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bots_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:47:23 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:47:24 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOTS_FUNCTIONS_H
# define BOTS_FUNCTIONS_H

# include "vm.h"

t_bot			*bot_new(int number, t_string *code);
t_bot			*bot_copy(t_bot *src);
void			bot_del(t_bot **bot);
void			bots_list_del(t_linked_list **head);
int				read_bot(t_string *code, char *file_name);

#endif
