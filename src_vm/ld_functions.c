/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:45:16 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:45:17 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ld_functions.h"

int			ld_lld_commands(t_data *data, t_bot *bot)
{
	if (get_arg_type(bot->command, bot->opcode, 1) == DIR_CODE)
		bot->reg[bot->args[1]] = bot->args[0];
	else if (bot->command == 2 &&
			(get_arg_type(bot->command, bot->opcode, 1) == IND_CODE))
		bot->reg[bot->args[1]] = get_number_from_bcode(data->map +
	(bot->pc + (bot->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
	else if (bot->command == 13 &&
			(get_arg_type(bot->command, bot->opcode, 1) == IND_CODE))
		bot->reg[bot->args[1]] = get_number_from_bcode(data->map +
			(bot->pc + bot->args[0] + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
	return (0);
}

void		ldi_lldi_commands(t_data *data, t_bot *bot)
{
	int		a[2];

	if (get_arg_type(bot->command, bot->opcode, 1) == REG_CODE)
		a[0] = bot->reg[bot->args[0]];
	else if (get_arg_type(bot->command, bot->opcode, 1) == DIR_CODE)
		a[0] = bot->args[0];
	else if (bot->command == 10 &&
			(get_arg_type(bot->command, bot->opcode, 1) == IND_CODE))
		a[0] = (get_number_from_bcode(data->map + (bot->pc + 2 +
			(bot->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, IND_SIZE));
	else if (bot->command == 14 && (get_arg_type(bot->command,
												bot->opcode, 1) == IND_CODE))
		a[0] = (get_number_from_bcode(data->map + (bot->pc + 2 +
			(bot->args[0]) + MEM_SIZE) % MEM_SIZE, IND_SIZE));
	if (get_arg_type(bot->command, bot->opcode, 2) == REG_CODE)
		(bot->command == 10) ? (a[1] = bot->reg[bot->args[1]] % IDX_MOD) :
		(a[1] = bot->reg[bot->args[1]]);
	else if (get_arg_type(bot->command, bot->opcode, 2) == DIR_CODE)
		a[1] = bot->args[1];
	if (bot->command == 10)
		bot->reg[bot->args[2]] = get_number_from_bcode(data->map +
	(bot->pc + ((a[0] + a[1]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
	else
		bot->reg[bot->args[2]] = get_number_from_bcode(data->map +
			(bot->pc + (a[0] + a[1]) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
}

int			ld_operations(t_data *data, t_bot *bot)
{
	if (bot->command == 2 || bot->command == 13)
	{
		ld_lld_commands(data, bot);
		(bot->reg[bot->args[1]] == 0) ? (bot->carry = 1) :
		(bot->carry = 0);
	}
	else
	{
		ldi_lldi_commands(data, bot);
		(bot->reg[bot->args[2]] == 0 &&
		bot->command == 14) ? (bot->carry = 1) :
		(bot->carry = 0);
	}
	return (0);
}
