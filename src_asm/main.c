/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:43:05 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:43:06 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	check_args(int *fd, int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("{red}Error:{eoc} wrong number of arguments.\n");
		exit(1);
	}
	if ((*fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_printf("{red}Error:{eoc} can't open file '%s'.\n", argv[1]);
		exit(1);
	}
	if (!ft_strchr(argv[1], '.') || (*(ft_strrchr(argv[1], '.') + 1) != 's') ||
			(*(ft_strrchr(argv[1], '.') + 2) != '\0'))
	{
		ft_printf("{red}Error:{eoc} wrong file '%s'.\n", argv[1]);
		exit(1);
	}
}

int			main(int argc, char **argv)
{
	int		fd;
	t_main	data;

	ft_bzero(&data, sizeof(t_main));
	check_args(&fd, argc, argv);
	data.code = new_data(30);
	read_data(fd, &(data.code));
	data.lex_strings = lex_analyze(&data, data.code);
	syntax_analyze(&data);
	if (data.errors == 0)
		write_bcode(argv[1], &data);
	del_bcode(&data.bcode);
	if (data.list != NULL)
		list_del(&(data.list),
				((t_put_label *)data.list->data)->del_put_label);
	del_label_table(&data.table);
	del_lex_strs(data.lex_strings);
	del_all_data(&data.code);
	close(fd);
	return (0);
}
