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
	if (	(*(ft_strrchr(argv[1], '.') + 1) != 's')
		||	(*(ft_strrchr(argv[1], '.') + 2) != '\0')	)
	{
		ft_printf("{red}Error:{eoc} wrong file '%s'.\n", argv[1]);
		exit(1);
	}
}

int 		main(int argc, char **argv)
{
	int 	fd;
	t_main	main;


	argv[1] = "/nfs/2016/r/rhakh/Corewar/Tests/jumper.s";
	argv[1] = "/nfs/2016/r/rhakh/Corewar/test_fork.s";


	ft_bzero(&main, sizeof(t_main));
	check_args(&fd, argc, argv);
	main.code = new_data(30);
	read_data(fd, &(main.code));
	main.lex_strings = lex_analyze(&main, main.code);
	syntax_analyze(&main);
	if (main.errors == 0)
		write_bcode(argv[1], &main);


	print_lex(main.lex_strings);
	print_label_table(main.table);
	print_bcode(main.bcode);


	del_bcode(&main.bcode);
	if (main.list != NULL)
		del_linked_list(&(main.list),
					((t_put_label *)main.list->data)->del_put_label);
	del_label_table(&main.table);
	del_lex_strs(&main.lex_strings);
	del_all_data(&main.code);
	close(fd);
	while (1);
	return (0);
}

//todo trim input string
//todo file without dot
//todo link table == NULL
/*
 	argv[1] = "/home/rhakh/Corewar/test_live.s";
//	argv[1] = "/home/rhakh/Corewar/jumper_test.s";
//	argv[1] = "/home/rhakh/Corewar/all_test.s";
//  argv[1] = "/nfs/2016/r/rhakh/Corewar/champs/jumper.s";
//  argv[1] = "/nfs/2016/r/rhakh/Corewar/champs/jumper.s";
    argv[1] = "/nfs/2016/r/rhakh/Corewar/test_link.s";
    argv[1] = "/nfs/2016/r/rhakh/Corewar/test_fork.s";
 *
 *
 *
 */