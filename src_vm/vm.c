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
** i from 1 to 3 must be
*/
char 		get_arg_type(char opcode, int i)
{
	char	arg_type;

	//		arg_type = (char)((opcode >> (4 - ((i) ? (1 << i) : (0)))) & 0b00000011);
	arg_type = 0;
	if (i == 1)
		arg_type = (char)((opcode >> 6) & 0b00000011);
	else if (i == 2)
		arg_type = (char)((opcode >> 4) & 0b00000011);
	else if (i == 3)
		arg_type = (char)((opcode >> 2) & 0b00000011);
	return (arg_type);
}

int 		get_args(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	char 			i;
	char 			arg_type;
	char 			offset;
	unsigned char 	*map;

	i = 0;
	offset = 0;
	map = data->map + bot->pc;
	while (i < op_tab[command - 1].n_arg)
	{
		arg_type = get_arg_type(opcode, i + 1);
		if (arg_type == REG_CODE)
		{
			args[i] = get_number_from_bcode(map + offset, 1);
			if (args[i] > REG_NUMBER || args[i] < 1)
				return (1);
			offset += 1;
		}
		else if (arg_type == DIR_CODE && op_tab[command - 1].dir_as_label)
		{
			args[i] = get_number_from_bcode(map + offset, IND_SIZE);
			offset += IND_SIZE;
		}
		else if (arg_type == DIR_CODE)
		{
			args[i] = get_number_from_bcode(map + offset, DIR_SIZE);
			offset += DIR_SIZE;
		}
		else if (arg_type == IND_CODE)
		{
			args[i] = get_number_from_bcode(map + offset, IND_SIZE);
			offset += IND_SIZE;
		}
		i++;
	}
	return (0);
}

int 		arithmetic_operations(t_bot *bot, char command, int args[3])
{
	if (command == 4)
		bot->reg[args[2]] = bot->reg[args[0]] + bot->reg[args[1]];
	else
		bot->reg[args[2]] = bot->reg[args[0]] - bot->reg[args[1]];
	bot->pause_time = op_tab[command - 1].cycles_to_done;
	return (0);
}

int 		logic_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	i;
	int 	num[2];
	char 	arg_type;

	i = 0;
	while (i < op_tab[command - 1].n_arg - 1)
	{
		arg_type = get_arg_type(opcode, i + 1);
		if (arg_type == REG_CODE)
			num[i] = bot->reg[args[i]];
		else if (arg_type == DIR_CODE)
			num[i] = bot->reg[args[i]];
		else if (arg_type == IND_CODE)
			num[i] = get_number_from_bcode(data->map + (bot->pc + (args[i] % IDX_MOD)), DIR_SIZE);
		i++;
	}
	(command == 6) ? (bot->reg[args[2]] = num[0] & num[1]) : 0;
	(command == 7) ? (bot->reg[args[2]] = num[0] | num[1]) : 0;
	(command == 8) ? (bot->reg[args[2]] = num[0] ^ num[1]) : 0;
	return (0);
}

int 		st_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (command == 3)
		put_number_to_bcode(data, bot->reg[args[0]], (bot->pc + (args[1] % IDX_MOD)));
//	if (send_to_ncurses((bot->pc + (args[1] % IDX_MOD)), DIR_SIZE, bot, data))
//		return (1);
	return (0);
}

int 		run_command(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (command == 4 || command == 5)
		arithmetic_operations(bot, command, args);
	if (command == 6 || command == 7 || command == 8)
		logic_operations(data, bot, command, opcode, args);
	if (command == 3 || command == 11)
		st_operations(data, bot, command, opcode, args);
	bot->pc++;
	return (0);
}

int 		execute_command(t_data *data, t_bot *bot)
{
	char 			command;
	char 			opcode;
	int 			args[3];

	opcode = 0;
	command = data->map[bot->pc];

	bot->pc++;
	if (op_tab[command - 1].have_opcode)
	{
		opcode = data->map[bot->pc];
		bot->pc++;
	}

	if (get_args(data, bot, command, opcode, args))
		return (1);

	bot->pc--;
	if (op_tab[command - 1].have_opcode)
		bot->pc--;

	if (run_command(data, bot, command, opcode, args))
		return (1);
	return (0);
}

/*
** 0 - ok , 1 - error
*/
int 		execute_commands(t_data *data)
{
	//todo hakh
	t_linked_list	*curr;
	t_bot			*bot;
	int 			min;

	min = 2147483647;
	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		if (min > bot->pause_time)
			min = bot->pause_time;
		curr = curr->next;
	}
	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		if (min == bot->pause_time)
		{
			if (execute_command(data, bot))
				return (1);
		}
		else
			bot->pause_time -= min;
		curr = curr->next;
	}
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		 infinit_loop(t_data *data)
{
	//todo:hakh execute bots commands
	//todo:bondar synchronized output using opengl
	t_linked_list	*curr;
	t_bot			*bot;

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
	int 			bot_number;
	int 			curr_number = 2147483647;

	i = 0;
	bot_number = 0;
	period = MEM_SIZE / data->bots_count;
	curr = data->bots;
	while (curr)
	{
		curr_bot = curr->data;
		curr_bot->reg[1] = curr_number;
		curr_bot->number = bot_number;
		ft_memcpy(data->map + i, curr_bot->code->str + sizeof(int) + PROG_NAME_LENGTH + sizeof(int) + sizeof(int) + COMMENT_LENGTH + sizeof(int), (size_t )curr_bot->size);
		i += period;
		curr = curr->next;
		curr_number--;
		bot_number++;
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
			if (data->map[i] == 0)
				ft_printf("%0.2hhx ", data->map[i]);
			else
				ft_printf("{green}%0.2hhx {eoc}", data->map[i]);
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
	argv[0] = "../test_st.cor";
	data.bots_count = 1;
	if (init_bots(&data, argv, 1))
		return (1);
	load_bots_in_memory(&data);
	//ft_display_arena(&data);
	if (infinit_loop(&data))
		return (1);
	print_memory(&data);
	//todo: calculate winner
	//todo:hakh free bots code (t_string)
}
