/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:48:40 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:48:41 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USAGE_H
# define USAGE_H

# include "vm.h"

int				usage(char **argv, int close_prog);
int				check_players_file_name(t_data *data);

#endif
