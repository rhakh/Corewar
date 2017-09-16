/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:45:54 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:45:55 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				print_dump(t_data *data)
{
	int		i;

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

int				sum_processes(t_data *data)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (++i < data->bots_count + 1)
		res += data->processes[i];
	return (res);
}

void			calculate_winner(t_data *data)
{
	int				i;
	int				nb;
	int				max;
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
	while (curr && (bot = curr->data))
	{
		if (bot && bot->number == nb && bot->name)
		{
			ft_printf("Player %d (%s) won\n", bot->number, bot->name);
			return ;
		}
		curr = curr->next;
	}
}

static void		initialization_vm(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->cycles_to_die = CYCLE_TO_DIE;
	data->next_cycles_check = CYCLE_TO_DIE;
	data->dump = -1;
	data->one_command_mode = 1;
	data->pause = 0;
	data->cycles = 0;
}

int				main(int argc, char **argv)
{
	t_data	data;

	initialization_vm(&data);
	if (argc == 1)
		usage(argv, 1);
	if (parse_flags(&data, argc, argv))
		return (1);
	if (init_bots(&data, data.players, data.bots_count))
	{
		bots_list_del(&(data.bots));
		return (1);
	}
	load_bots_in_memory(&data);
	(data.visual) ? (nc_display_arena(&data)) : 0;
	first_pause(&data);
	if (infinit_loop(&data))
	{
		bots_list_del(&(data.bots));
		return (1);
	}
	(data.visual) ? (nc_terminate(&data)) : (calculate_winner(&data));
	bots_list_del(&(data.bots));
	return (0);
}
