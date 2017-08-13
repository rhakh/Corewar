/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 09:58:06 by apalanic          #+#    #+#             */
/*   Updated: 2017/08/06 09:58:26 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wm.h"

void	print(t_data *data)
{
//	ft_printf("dump:%d\n", data->dump);
	int	i = -1;
	ft_printf("bot count: %d\n", data->bot_cnt);
	while (++i < 4)
	{
		ft_printf ("%s\n", data->players[i]);
	}

}

//int		main(int argc, char **argv)
//{
//	t_data	data;
//
//	if (argc == 1)
//		usage();
//	parse_flags(&data, argc, argv);
//	print(&data);
//	return (0);
//}
