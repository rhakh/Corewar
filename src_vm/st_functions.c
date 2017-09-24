/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:45:47 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:45:48 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st_functions.h"

int			st_command(t_data *data, t_bot *bot)
{
	put_number_to_bcode(data, bot->reg[bot->args[0]], ((bot->pc +
				(bot->args[1] % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	(data->visual) ? (ncurses_change_memory(((bot->pc +
				(bot->args[1] % IDX_MOD)) + MEM_SIZE) % MEM_SIZE,
					bot, data)) : 0;
	return (0);
}

int			sti_command(t_data *data, t_bot *bot)
{
	if (get_arg_type(bot->command, bot->opcode, 2) == IND_CODE)
		bot->args[1] = get_number_from_bcode(data->map + (bot->pc + 2 +
			(bot->args[1] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, IND_SIZE);
	else if (get_arg_type(bot->command, bot->opcode, 2) == REG_CODE)
		bot->args[1] = bot->reg[bot->args[1]] % IDX_MOD;
	else
		bot->args[1] = bot->args[1] % IDX_MOD;
	if (get_arg_type(bot->command, bot->opcode, 3) == REG_CODE)
		bot->args[2] = bot->reg[bot->args[2]] % IDX_MOD;
	else
		bot->args[2] = bot->args[2] % IDX_MOD;
	put_number_to_bcode(data, bot->reg[bot->args[0]], ((bot->pc +
		((bot->args[1] + bot->args[2]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	(data->visual) ? (ncurses_change_memory(((bot->pc +
		((bot->args[1] + bot->args[2]) % IDX_MOD)) + MEM_SIZE) % MEM_SIZE,
		bot, data)) : 0;
	return (0);
}

int			st_operations(t_data *data, t_bot *bot)
{
	if (bot->command == 3)
		st_command(data, bot);
	else
		sti_command(data, bot);
	return (0);
}
