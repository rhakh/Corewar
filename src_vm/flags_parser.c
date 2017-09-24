/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 10:24:09 by apalanic          #+#    #+#             */
/*   Updated: 2017/09/16 13:40:01 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags_parser.h"

static int		add_new_player(t_data *data, int *i, char **argv)
{
	int		j;

	j = 0;
	while (++j < (MAX_PLAYERS + 1))
		if (data->players[j] == NULL)
		{
			data->players[j] = argv[*i];
			break ;
		}
	if (j == (MAX_PLAYERS + 1))
	{
		ft_printf("{red}Too much players{eoc}\n");
		return (1);
	}
	data->bots_count++;
	return (0);
}

static int		add_n_player(t_data *data, int *i, int argc, char **argv)
{
	if (*i + 1 >= argc)
	{
		ft_printf("{red}Wrong number of player or player not empty{eoc}\n");
		return (1);
	}
	if ((ft_atoi(argv[*i + 1]) >= 1 && ft_atoi(argv[*i + 1]) <= 4) &&
		(*i + 2 < argc) && ft_atoi(argv[*i + 1]) >= 1 && ft_atoi(argv[*i + 1])
		<= (MAX_PLAYERS + 1) && data->players[ft_atoi(argv[*i + 1])] == NULL)
	{
		data->players[ft_atoi(argv[*i + 1])] = argv[*i + 2];
		(*i) += 2;
	}
	else
	{
		ft_printf("{red}Wrong number of player or player not empty{eoc}\n");
		return (1);
	}
	data->bots_count++;
	return (0);
}

int				first_part_while(char **argv, int *i, int argc, t_data *data)
{
	if ((!ft_strcmp("-h", argv[*i]) || !ft_strcmp("--help", argv[*i])) &&
			(usage(argv, 0)))
		return (1);
	else if (!ft_strcmp("-dump", argv[*i]))
	{
		if (*i + 1 < argc)
			data->dump = ft_atoi(argv[++(*i)]);
		else
		{
			ft_printf("{red}Dump is empty\n{eoc}");
			return (1);
		}
		return (0);
	}
	else if (!ft_strcmp("-v", argv[*i]))
	{
		data->visual = 1;
		return (0);
	}
	else if (!ft_strcmp("-m", argv[*i]))
	{
		data->mute = 1;
		return (0);
	}
	return (2);
}

int				second_part_while(char **argv, int *i, int argc, t_data *data)
{
	if (!ft_strcmp("-n", argv[*i]))
	{
		if (add_n_player(data, i, argc, argv))
			return (1);
	}
	else if (!ft_strcmp("-debug", argv[*i]))
	{
		if (*i + 1 < argc)
			data->debug_level = atoi(argv[*i + 1]);
		else
		{
			ft_printf("{red}-debug option required number{eoc}\n");
			return (1);
		}
		(*i)++;
	}
	else
	{
		if (add_new_player(data, i, argv))
			return (1);
	}
	return (0);
}

int				parse_flags(t_data *data, int argc, char **argv)
{
	int		i;
	int		ret;

	i = 1;
	while (i < argc)
	{
		ret = first_part_while(argv, &i, argc, data);
		if (ret == 1)
			return (1);
		if (ret == 2)
		{
			if (second_part_while(argv, &i, argc, data) == 1)
				return (1);
		}
		i++;
	}
	return (check_players_file_name(data));
}
