/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 10:24:09 by apalanic          #+#    #+#             */
/*   Updated: 2017/08/06 10:24:11 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ***************************************** ********************************* */

#include "flags_parser.h"

void	usage(char **argv)
{
//	ft_putstr_fd("\t** --------------------USAGE--------------------\n\
//\t** ./corewar [-h || --help] to view this massege\n \
//\t** Example: ./corewar -v -n 3 player.cor\n \
//\t** GUI: ./corewar -v [player1.cor player2.cor...]\n \
//\t** Default player numbers: 1, 2, 3, 4 [This numbers only for -n\n \
//\t** Change player number: -n -[number] player.cor\n \
//\t** Dump: ./corewar -dump 50 [Players] -> it will print the memory after \
//50 cycles\n", 2);

	ft_printf("{yellow}\t\t\t\t\tUsage:{eoc}\n"
		"\t%s [-n <number 1 .. 4> player.cor] [-v] "
		"[-dump <number>] [-debug <number>] player.cor\n"
		"\t-h - --help - print this message\n"
		"\t-v - for enable visual mode\n"
		"\t-n - to set different player number\n"
		"\t-m - mute\n"
		"\t-dump - print dump of memory at some cycle, to stdout\n"
		"\t-debug - debug level\n"
		"\t\t- 0 : show only winner (default)\n"
		"\t\t- 1 : show lives\n"
		"\t\t- 2 : show cycles\n"
		"\t\t- 4 : show operations and their arguments\n", argv[0]);
	exit(1);
}

int				parse_flags(t_data *data, int argc, char **argv)
{
	int 	i;
	int 	j;
	char 	*p;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp("-h", argv[i]) || !ft_strcmp("--help", argv[i]))
		{
			usage(argv);
			return (1);
		}
		else if (!ft_strcmp("-dump", argv[i]))
		{
			if (i + 1 < argc)
				data->dump = ft_atoi(argv[i + 1]);
			else
				ft_printf("{red}Dump is empty\n{eoc}");
			i++;
		}
		else if (!ft_strcmp("-v", argv[i]))
			data->visual = 1;
		else if (!ft_strcmp("-m", argv[i]))
			data->mute = 1;
		else if (!ft_strcmp("-n", argv[i]))
		{
			if ((i + 2 < argc) && ft_atoi(argv[i + 1]) >= 1 && ft_atoi(argv[i + 1]) <= (MAX_PLAYERS + 1) && data->players[ft_atoi(argv[i + 1])] == NULL)
			{
				data->players[ft_atoi(argv[i + 1])] = argv[i + 2];
				i += 2;
			}
			else
			{
				ft_printf("{red}Wrong number of player or player not empty{eoc}\n");
				return (1);
			}
			data->bots_count++;
		}
		else if (!ft_strcmp("-debug", argv[i]))
		{
			if (i + 1 < argc)
				data->debug_level = atoi(argv[i + 1]);
			else
			{
				ft_printf("{red}-debug option required number{eoc}\n");
				return (1);
			}
			i++;
		}
		else
		{
			j = 0;
			while (++j < (MAX_PLAYERS + 1))
				if (data->players[j] == NULL)
				{
					data->players[j] = argv[i];
					break ;
				}
			if (j == (MAX_PLAYERS + 1))
			{
				ft_printf("{red}Too much players{eoc}\n");
				return (1);
			}
			data->bots_count++;
		}
		i++;
	}
	i = 1;
	while (i < (MAX_PLAYERS + 1) && i < (data->bots_count + 1))
	{
		p = 0;
		(data->players[i]) ? (p = ft_strrchr(data->players[i], '.')) : 0;
		if (p)
		{
			if (p[1] != 'c' || p[2] != 'o' || p[3] != 'r' || p[4] != '\0')
			{
				ft_printf("{red}Wrong player name '%s'{eoc}\n", data->players[i]);
				return (1);
			}
		}
		else
		{
			ft_printf("{red}Empty slot for player # %d\n{eoc}", i);
			return (1);
		}
		i++;
	}
	return (0);
}
