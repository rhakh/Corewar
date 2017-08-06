#include "../new_libft/srcs/libft.h"
#include "vm.h"

/*
** 0 - ok , 1 - error
*/
int 		listen_keybord(t_data *data)
{
	//todo sbondar
	//if space was pressed then data->pause must be stalled in 1
	//if space was pressed again then data->pause = 0
	//if right-arrow was pressed then data->one_command_mode = 1
	return (0);
}

/*
** 0 - ok , 1 - error
*/
int 		execute_commands(t_data *data)
{
	//todo hakh
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		infinit_loop(t_data *data)
{
	//todo:hakh execute bots commands
	//todo:bondar synchronized output using opengl
	while (1)
	{
		if (listen_keybord(data))
			return (1);
		if (!data->pause || data->one_command_mode)
		{
			if (execute_commands(data))
				return (1);
			//todo calculate cycles and winner
			data->one_command_mode = 0;
		}
		break; //delete this
	}
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		init_bots(t_data *data, char **argv, int num)
{
	//todo:hakh write bots code to t_string, validate it, load into map
	int 		i;
	int 		ret;
	t_string	*curr;
	t_bot		*bot;

	i = 0;
	ret = 0;
	while (i < MAX_PLAYERS && i < num)
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
		list_push_back(&(data->bots), bot);
		i++;
	}
	if (validate_bots(data))
	{
		list_del(&(data->bots), bot_del);
		return (1);
	}
	return (0);
}

void		load_bots_in_memory(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*curr_bot;
	int 			period;
	int 			i;

	i = 0;
	period = MEM_SIZE / data->bots_count;
	curr = data->bots;
	while (curr)
	{
		curr_bot = curr->data;
		ft_memcpy(data->map + i, curr_bot->code->str + sizeof(int) + PROG_NAME_LENGTH + sizeof(int) + sizeof(int) + COMMENT_LENGTH + sizeof(int), (size_t )curr_bot->size);
		i += period;
		curr = curr->next;
	}
}

void		print_memory(t_data *data)
{
	int 	i;

	i = 0;
	ft_printf("{yellow}Memory dump:\n{eoc}");
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		ft_printf("%0.2hhx ", data->map[i]);
		i++;
	}
}

int         main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	//todo:palanich process arguments and return ordered array of bots names
	//todo:hakh
	argv[0] = "../champs/jumper.cor";
	argv[0] = "../test_comment.ror";
	data.bots_count = 1;
	if (init_bots(&data, argv, 1))
		return (1);
	load_bots_in_memory(&data);
	print_memory(&data);
	if (infinit_loop(&data))
		return (1);
	//todo: calculate winner
	//todo:hakh free bots code (t_string)
}
