/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_infinit_cycle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 20:24:57 by dtelega           #+#    #+#             */
/*   Updated: 2017/09/13 20:19:41 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "sdl_vm.h"

void		ncurses_speed(t_data *data, char key)
{
	if (data->ncurses_timeout > 0 && data->ncurses_timeout < 1024)
		(!data->mute) ? (sdl_sound(MUS_SPEED)) : 0;
	if (key == NC_SPEED_UP)
		data->ncurses_timeout /= 2;
	else
	{
		if (data->ncurses_timeout == 0)
			data->ncurses_timeout = 1;
		else
			data->ncurses_timeout *= 2;
	}
	if (data->ncurses_timeout < 0)
		data->ncurses_timeout = 0;
	else if (data->ncurses_timeout > 1024)
		data->ncurses_timeout = 1024;
}

char		ncurses_one_cm_mode(t_data *data, char pause)
{
	data->one_command_mode = 0;
	pause = NC_PAUSE_1;
	data->pause = 1;
	display_stats(data, data->stats_win);
	refresh();
	return (pause);
}

char		ncurses_cycle_pause(t_data *data, char pause)
{
	data->pause = 0;
	display_stats(data, data->stats_win);
	refresh();
	(!data->mute) ? (sdl_sound(MUS_BEEP)) : 0;
	return ('q');
}

char		ncurses_global_cycle(t_data *data, char pause)
{
	char	cmd;

	data->pause = 1;
	display_stats(data, data->stats_win);
	refresh();
	cmd = getch();
	if (cmd == NC_SPEED_UP || cmd == NC_SPEED_DOWN)
		ncurses_speed(data, cmd);
	if (cmd == NC_PAUSE_1 || cmd == NC_PAUSE_2)
		pause = ncurses_cycle_pause(data, pause);
	else if (cmd == NC_ONE_COMM_MOD && (data->one_command_mode = 1))
		return (NC_ONE_COMM_MOD);
	return (pause);
}

void		ncurses_visual(t_data *data)
{
	int		pause;

	timeout(data->ncurses_timeout);
	pause = getch();
	if (pause == NC_SPEED_DOWN || pause == NC_SPEED_UP)
		ncurses_speed(data, pause);
	if (data->one_command_mode)
		pause = ncurses_one_cm_mode(data, pause);
	if ((pause == NC_PAUSE_1 || pause == NC_PAUSE_2))
	{
		(!data->mute) ? (sdl_sound(MUS_BEEP)) : 0;
		while (pause == NC_PAUSE_1 || pause == NC_PAUSE_2)
			pause = ncurses_global_cycle(data, pause);
	}
	(pause == NC_ONE_COMM_MOD) ? (data->one_command_mode = 1) : 0;
}
