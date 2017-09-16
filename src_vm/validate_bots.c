#include "validate_bots.h"

int			validate_magic_number(t_bot *bot)
{
	int		mag_num;

	mag_num = get_number_from_bcode(
			(const unsigned char *)bot->code->str, sizeof(int));
	if (mag_num == COREWAR_EXEC_MAGIC)
		return (0);
	ft_printf("Incorrect magic number\n");
	return (1);
}

int			validate_bot_size(t_bot *bot)
{
	int		size1;
	int		size2;

	size1 = get_number_from_bcode((unsigned char *)
				bot->code->str + 8 + PROG_NAME_LENGTH, sizeof(int));
	size2 = (int)bot->code->len - sizeof(int) -
			PROG_NAME_LENGTH - 12 - COMMENT_LENGTH;
	if (size1 != size2)
	{
		ft_printf("{red}Error:{eoc} declared and actual size are"
					"not equal %d != %d\n", size1, size2);
		return (1);
	}
	if (size1 > CHAMP_MAX_SIZE)
	{
		ft_printf("{red}Error:{eoc} champ size is too big, "
					"max size = %d\n", CHAMP_MAX_SIZE);
		return (1);
	}
	bot->size = size1;
	return (0);
}

/*
** 0 - ok, 1 - error
*/

int			validate_bots(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*curr_bot;
	int				i;

	i = 1;
	curr = data->bots;
	while (curr)
	{
		curr_bot = (t_bot *)curr->data;
		if (validate_magic_number(curr_bot))
			return (1);
		if (validate_bot_size(curr_bot))
			return (1);
		curr_bot->name = ft_strndup(curr_bot->code->str +
			sizeof(int), PROG_NAME_LENGTH);
		curr_bot->comment = ft_strndup(curr_bot->code->str +
			sizeof(int) + PROG_NAME_LENGTH + 4 + sizeof(int), COMMENT_LENGTH);
		ft_memcpy(data->bots_names[i], curr_bot->name,
			ft_strlen(curr_bot->name));
		i++;
		curr = curr->next;
	}
	return (0);
}

int			aff_operation(t_data *data, t_bot *bot)
{
	if (data->visual)
		ncurses_aff(data, bot, bot->args[0]);
	else
		ft_printf("Player %d: reg[%d] = %d '%c'\n",
				bot->number, bot->args[0], bot->reg[bot->args[0]],
				(bot->reg[bot->args[0]] >= 32
				&& bot->reg[bot->args[0]] <= 126) ?
				(bot->reg[bot->args[0]]) : (32));
	return (0);
}

int			run_command(t_data *data, t_bot *bot)
{
	int		ret;

	ret = 0;
	if (bot->command == 4 || bot->command == 5)
		ret = arithmetic_operations(bot);
	else if (bot->command == 6 || bot->command == 7 || bot->command == 8)
		ret = logic_operations(data, bot);
	else if (bot->command == 3 || bot->command == 11)
		ret = st_operations(data, bot);
	else if (bot->command == 2 || bot->command == 10 || bot->command == 13
			|| bot->command == 14)
		ret = ld_operations(data, bot);
	else if (bot->command == 12 || bot->command == 15)
		ret = fork_operations(data, bot);
	else if (bot->command == 1)
		ret = live_operation(data, bot);
	else if (bot->command == 9)
		ret = zjmp_operation(bot);
	else if (bot->command == 16)
		ret = aff_operation(data, bot);
	return (ret);
}
