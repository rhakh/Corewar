#include "vm.h"

void		print_memory(t_data *data)
{
	int 	i;

	i = 0;
	ft_printf("{yellow}Memory dump:\n{eoc}");
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		if (data->map[i] == 0)
			ft_printf("%0.2hhx ", data->map[i]);
		else
			ft_printf("{green}%0.2hhx {eoc}", data->map[i]);
		i++;
	}
	ft_printf("\n");
}


int			print_dump(t_data *data)
{
	int 	i;

	i = 0;
	ft_printf("{yellow}Memory dump:\n{eoc}");
	while (i < MEM_SIZE)
	{
		if (data->map[i])
			ft_printf("{green}%02hhx {eoc}", data->map[i]);
		else
			ft_printf("%02hhx ", data->map[i]);
		i++;
		if (i > 0 && i % 64 == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
	return (0);
}

int	summ_processes(t_data *data)
{
	int 	i;
	int 	res;

	i = 0;
	res = 0;
	while (++i < data->bots_count + 1)
		res += data->processes[i];
	return (res);
}

/*
** 0 - ok, 1 - error
*/
int 		 infinit_loop(t_data *data)
{
	int		pause;
	int 	next_command;

	next_command = data->pause_time - 1;
	while (data->cycles_to_die > 0 && summ_processes(data) > 0)
	{
		if (data->visual)
		{
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

		if (!data->pause || data->one_command_mode)
		{
			if (data->dump == data->cycles && !data->visual)
				print_dump(data);

			if (data->cycles == data->next_cycles_check)
			{
				check_for_live_bots(data);
				data->next_cycles_check = data->cycles + data->cycles_to_die;
				data->max_checks++;
				if (data->max_checks > 0 && (data->max_checks % MAX_CHECKS == 0))
				{
					if (data->last_cycles_to_die == data->cycles_to_die)
					{
						(data->cycles_to_die - CYCLE_DELTA > 0) ? (data->cycles_to_die -= CYCLE_DELTA) : (data->cycles_to_die = 0);
						data->next_cycles_check = data->cycles + data->cycles_to_die;
					}
					data->last_cycles_to_die = data->cycles_to_die;
				}
			}

			if (next_command <= 0)
			{
				if (execute_commands(data))
					return (1);
				next_command = data->pause_time;
			}

			next_command--;
			data->cycles++;
		}

		if (data->visual)
		{
			display_stats(data, data->stats_win);
			wrefresh(data->memory_win);
			refresh();
		}
	}
	return (0);
}


/*
** 0 - ok, 1 - error
*/
int 		init_bots(t_data *data, char *argv[MAX_PLAYERS + 1], int num)
{
	int 		i;
	int 		ret;
	t_string	*curr;
	t_bot		*bot;

	i = 1;
	ret = 0;
	while (i < (MAX_PLAYERS + 1) && i < (num + 1))
	{
		curr = string_new(30);
		(read_bot(curr, argv[i])) ? (ret = 1) : 0;
		(bot = bot_new(i + 1, curr)) ? 0 : (ret = 1);
		if (ret)
		{
			list_del(&(data->bots), bot_del);
			string_del(&curr);
			return (1);
		}
		bot->last_live = 0;
		bot->is_dead = 0;
		bot->prev_attr = -1;
		data->bots_tail = list_push_back(&(data->bots), bot);
		i++;
	}
	if (validate_bots(data) || data->bots_count == 0)
	{
		list_del(&(data->bots), bot_del);
		(data->bots_count == 0) ? (ft_printf("{red}Bots count = 0\n{eoc}")) : 0;
		return (1);
	}
	return (0);
}

void		calculate_winner(t_data *data)
{
	int 	i;
	int 	nb;
	int 	max;
	t_linked_list	*curr;
	t_bot			*bot;

	i = 1;
	nb = 1;
	max = data->bots_last_live[1];
	while (++i <= data->bots_count)
		if (data->bots_last_live[i] > max)
		{
			max = data->bots_last_live[i];
			nb = i;
		}
	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		if (bot->number == nb && bot->name)
		{
			ft_printf("%sPlayer %d (%s) won\n"EOCP, bot->color, bot->number, bot->name);
			return ;
		}
		curr = curr->next;
	}
}

void		load_bots_in_memory(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*curr_bot;
	int 			period;
	int 			i;
	int 			bot_number;
	int 			r1_number = -1;

	i = 0;
	bot_number = 1;
	period = MEM_SIZE / data->bots_count;
	curr = data->bots;
	while (curr)
	{
		curr_bot = curr->data;
		curr_bot->reg[1] = r1_number;
		curr_bot->r1_number = r1_number;
		curr_bot->number = bot_number;
		curr_bot->pc = i;
		curr_bot->start = i;
		data->processes[curr_bot->number]++;
		ft_memcpy(data->map + i, curr_bot->code->str + 4 + PROG_NAME_LENGTH + 4	 + 4 + COMMENT_LENGTH + 4, (size_t )curr_bot->size);
		i += period;
		curr = curr->next;
		r1_number--;
		bot_number++;
	}
}

int         main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.cycles_to_die = CYCLE_TO_DIE;
	data.next_cycles_check = CYCLE_TO_DIE;
	data.dump = -1;
	data.one_command_mode = 1;
	data.pause = 0;
	data.cycles = 0;
	if (argc == 1)
		usage(argv);
	if (parse_flags(&data, argc, argv))
		return (1);
	if (init_bots(&data, data.players, data.bots_count))
	{
		list_del(&(data.bots), bot_del);
		return (1);
	}
	load_bots_in_memory(&data);
	(data.visual) ? (nc_display_arena(&data)) : 0;
	first_pause(&data);
	if (infinit_loop(&data))
	{
		list_del(&(data.bots), bot_del);
		return (1);
	}
	(data.visual) ? (nc_terminate(&data)) : (calculate_winner(&data));
	list_del(&(data.bots), bot_del);
	return (0);
}
