/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 13:06:31 by apalanic          #+#    #+#             */
/*   Updated: 2017/08/06 13:06:33 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags_parser.h"

static void	save_bot_filename(t_data *data, int *i, char **argv, int k)
{
	size_t		len;
	static int	check[4];
	static int	j;
	int			l;

	j = 0;
	l = -1;
	while (++l < 4)
	{
		if (check[l] == k)
			exit_error(data, 9);
	}
	check[j++] = k;
	(*i)++;
	len = ft_strlen(argv[*i]);
	if (ft_strncmp(".cor", &argv[*i][len - 4], 4))
		exit_error(data, 16);
	data->players[j] = ft_strdup(argv[*i]);
}

void		add_wn(t_data *data, int *i, char **argv, int argc)
{
	int	tmp;
	int	j;
	int k;

	j = -1;
	k = 0;

	while ((*i) < argc)
	{
		(!ft_strcmp("-n", argv[*i])) ? ((*i)++) : exit_error(data, 21);
		if (!ft_isdigit(argv[*i][0]))
			exit_error(data, 14);
		if (ft_strlen(argv[*i]) > 1)
			exit_error(data, 21);
		tmp = ft_atoi(argv[*i]);
		if (tmp > 4 || tmp < 1)
			exit_error(data, 21);
		save_bot_filename(data, i, argv, tmp);
		data->bots_count++;
		if (data->bots_count > MAX_PLAYERS)
			exit_error(data, 8);
		(*i)++;
	}
}

void		add_player(t_data *data, int *i, char **argv, int argc)
{
	size_t	len;
	int		k;

	k = 0;
	while ((*i) < argc)
	{
		len = ft_strlen(argv[*i]);
		if (ft_strncmp(".cor", &argv[*i][len - 4], 4))
			exit_error(data, 16);
		data->players[k++] = ft_strdup(argv[*i]);
		data->bots_count++;
		if (data->bots_count > MAX_PLAYERS)
			exit_error(data, 8);
		(*i)++;
	}
	data->players[k] = NULL;
}
