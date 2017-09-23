/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bcode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:42:02 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:42:03 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			write_one_arg(int fd, unsigned int arg, int i)
{
	char		a;

	while (i >= 0)
	{
		a = (unsigned char)(arg >> i);
		write(fd, &a, 1);
		i -= 8;
	}
}

static void		write_to_file(int fd, t_main *main)
{
	t_bcode		*curr;

	curr = main->bcode;
	while (curr != NULL)
	{
		write(fd, curr->oper_number, 1);
		if (g_tab[*curr->oper_number - 1].have_opcode)
			write(fd, curr->op_code, 1);
		write_args(fd, curr);
		curr = curr->next;
	}
}

static void		write_header(int fd, t_main *main)
{
	int			zero;

	zero = 0;
	write_one_arg(fd, COREWAR_EXEC_MAGIC, 24);
	write(fd, main->name, PROG_NAME_LENGTH);
	write_one_arg(fd, (unsigned)zero, 24);
	write_one_arg(fd, (unsigned int)main->pc, 24);
	write(fd, main->comment, COMMENT_LENGTH);
	write_one_arg(fd, (unsigned)zero, 24);
}

static void		edit_file_name(char *file_name, char *src_name)
{
	ft_strcpy(file_name, src_name);
	*(ft_strrchr(file_name, '.') + 1) = 'c';
	*(ft_strrchr(file_name, '.') + 2) = 'o';
	*(ft_strrchr(file_name, '.') + 3) = 'r';
	*(ft_strrchr(file_name, '.') + 4) = '\0';
}

void			write_bcode(char *src_name, t_main *main)
{
	char		*file_name;
	int			fd;

	if (!main->comm_exist || !main->name_exist)
	{
		print_error(" name/comment is wrong or doesn't exist", NULL);
		return ;
	}
	if ((file_name = ft_strnew(ft_strlen(src_name + 4))) == NULL)
		return ;
	edit_file_name(file_name, src_name);
	fd = open(file_name, O_RDWR | O_CREAT |
						O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_printf("{red}Error:{eoc} can't create file.");
		free(file_name);
		return ;
	}
	write_header(fd, main);
	write_to_file(fd, main);
	ft_printf("{green}Write to file:{eoc} %s\n", file_name);
	free(file_name);
	close(fd);
}
