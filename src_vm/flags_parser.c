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

void			save_dump(t_data *data, char *num, int *i, int argc)
{
	int			tmp;
	int			j;

	j = -1;
	if ((*i + 3) > argc)
		exit_error(data, 11);
	(*i)++;
	while (num[++j] != '\0')
		if (!ft_isdigit(num[j]))
			exit_error(data, 14);
	if (ft_strlen(num) > 4)
		exit_error(data, 12);
	tmp = ft_atoi(num);
	if (tmp > CYCLE_TO_DIE)
		exit_error(data, 19);
	else
		data->dump = (size_t)tmp;
	(*i)++;
}

static void	print_parse(t_data *data)
{
//	ft_printf("dump:%d\n", data->dump);
	int	i = -1;
	ft_printf("bot count: %d\n", data->bots_count);
	while (++i < 4)
	{
		ft_printf ("%s\n", data->players[i]);
	}
}

//int				parse_flags(t_data *data, int argc, char **argv)
//{
//	int			i;
//
//	i = 1;
//	if (!ft_strcmp("-h", argv[i]) || !ft_strcmp("--help", argv[i]))
//	{
//		usage();
//		return (1);
//	}
//	if (!ft_strcmp("-dump", argv[i]))
//		save_dump(data, argv[i + 1], &i, argc);
//	else if (!ft_strcmp("-v", argv[i]))
//    {
//        data->visual = 1;
//        i++;
//    }
//    if (!ft_strcmp("-n", argv[i]))
//		add_wn(data, &i, argv, argc);
//	else
//		add_player(data, &i, argv, argc);
//	if (data->bots_count > MAX_PLAYERS)
//		exit_error(data, 8);
//	print_parse(data);
//	return (0);
//}

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
			usage();
			return (1);
		}
		else if (!ft_strcmp("-dump", argv[i]))
		{
			data->dump = (size_t)ft_atoi(argv[i + 1]);
			i++;
		}
		else if (!ft_strcmp("-v", argv[i]))
			data->visual = 1;
		else if (!ft_strcmp("-n", argv[i]))
		{
			if (ft_atoi(argv[i + 1]) >= 1 && ft_atoi(argv[i + 1]) <= (MAX_PLAYERS + 1) && data->players[ft_atoi(argv[i + 1])] == NULL)
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
	while (i < (MAX_PLAYERS + 1))
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
		i++;
	}
	return (0);
}
