#include "main.h"

static void		write_one_arg(int fd, unsigned int arg, int i)
{
	char 	a;

	while (i >= 0)
	{
		a = (unsigned char)(arg >> i);
		write(fd, &a, 1);
		i -= 8;
	}
}

static void		write_args(int fd, t_bcode *curr)
{
	int 		i;

	i = 0;
	while (curr->arg_type[i] != 0)
	{
		if (curr->arg_type[i] == T_DIR)
			(op_tab[*curr->oper_number - 1].dir_as_label) ?
			(write_one_arg(fd, (unsigned int)curr->args[i], 8)) :
			(write_one_arg(fd, (unsigned int)curr->args[i], 24));
		else if (curr->arg_type[i] == T_IND)
			write_one_arg(fd, (unsigned int)curr->args[i], 8);
		else if (curr->arg_type[i] == T_REG)
			write(fd, curr->args + i, 1);
		i++;
	}
}

static void		write_to_file(int fd, t_main *main)
{
	t_bcode		*curr;

	curr = main->bcode;
	while (curr != NULL)
	{
		write(fd, curr->oper_number, 1);
		if (op_tab[*curr->oper_number - 1].have_opcode)
			write(fd, curr->op_code, 1);
		write_args(fd, curr);
		curr = curr->next;
	}
}

int 			write_header(int fd, t_main *main)
{
	char 		c;

	c = 0;
	if (!main->comm_exist || !main->name_exist)
		return (0);
	write_one_arg(fd, COREWAR_EXEC_MAGIC, 24);
	write(fd, main->name, PROG_NAME_LENGTH);
	write(fd, &c, 1);
	write_one_arg(fd, (unsigned int)main->pc, 24);
	write(fd, main->comment, COMMENT_LENGTH);
	write(fd, &c, 1);
	return (1);
}

void			write_bcode(char *src_name, t_main *main)
{
	char		*file_name;
	int			fd;

	if ((file_name = ft_strnew(ft_strlen(src_name + 4))) == NULL)
		return ;
	ft_strcpy(file_name, src_name);
	*(ft_strrchr(file_name, '.') + 1) = 'c';
	*(ft_strrchr(file_name, '.') + 2) = 'o';
	*(ft_strrchr(file_name, '.') + 3) = 'r';
	*(ft_strrchr(file_name, '.') + 4) = '\0';
	ft_printf("\n%s\n", file_name);
	fd = open(file_name, O_RDWR | O_CREAT |
						 O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_printf("{red}Error:{eoc} can't create file.");
		free(file_name);
		return ;
	}
	if (!write_header(fd, main))
	{
		free(file_name);
		return ;
	}
	write_to_file(fd, main);
	close(fd);
}
