#include "vm.h"

void		ncurses_speed(t_data *data, char key)
{
	if (key == 's')
		data->ncurses_timeout /= 2;
	else
	{
		if (data->ncurses_timeout == 0)
			data->ncurses_timeout = 1;
		else
			data->ncurses_timeout *= 2;
	}
	data->ncurses_timeout < 0 ? data->ncurses_timeout = 0 : 0;
	data->ncurses_timeout > 1024 ? data->ncurses_timeout = 1024 : 0;
}

char		ncurses_one_cm_mode(t_data *data, char pause)
{
	data->one_command_mode = 0;
	pause = ' ';
	data->pause = 1;
	display_stats(data, data->stats_win);
	refresh();
	return (pause);
}

char 		ncurses_cycle_pause(t_data *data, char pause)
{
	data->pause = 0;
	display_stats(data, data->stats_win);
	refresh();
	return ('q');
}

char 		ncurses_global_cycle(t_data *data, char pause)
{
	char 	cmd;

	data->pause = 1;
	display_stats(data, data->stats_win);
	refresh();
	cmd = getch();
	if (cmd == 'a' || cmd == 's')
		ncurses_speed(data, cmd);
	if (cmd == ' ')
		pause = ncurses_cycle_pause(data, pause);
	else if (cmd == 'n' && (data->one_command_mode = 1))
		return ('n');
	return (pause);
}