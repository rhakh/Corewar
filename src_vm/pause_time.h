/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:48:22 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:48:24 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAUSE_TIME_H
# define PAUSE_TIME_H

# include "vm.h"

int		first_pause(t_data *data);
void	set_bot_pause_time(t_data *data, t_bot *bot);

#endif
