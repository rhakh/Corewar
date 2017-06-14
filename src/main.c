#include "main.h"

int 	main(int argc, char **argv)
{
	int 			fd;
	t_main			main;

	ft_bzero(&main, sizeof(t_main));
//	argv[1] = "/home/rhakh/Corewar/test_live.s";
//    argv[1] = "/nfs/2016/r/rhakh/Corewar/champs/jumper.s";
//    argv[1] = "/nfs/2016/r/rhakh/Corewar/champs/jumper.s";
    argv[1] = "/nfs/2016/r/rhakh/Corewar/test_link.s";
	if (argc != 2)
	{
		ft_printf("{red}Error:{eoc} wrong number of arguments.\n");
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_printf("{red}Error:{eoc} can't open file '%s'.\n", argv[1]);
		exit(2);
	}
	main.list = NULL;
	main.code = new_data(30);
	read_data(fd, &(main.code));
	print_data(main.code);

	main.lex_strings = lex_analyze(main.code);
	print_lex(main.lex_strings);

	syntax_analyze(&main);

	del_bcode(&main.bcode);
	if (main.list != NULL)
		del_linked_list(&main.list, ((t_put_label *)main.list->data)->del_put_label);
	del_label_table(&main.table);
	del_lex_strs(&main.lex_strings);
	del_all_data(&main.code);
	close(fd);
	return (0);
}

//todo trim input string
/*
 * argv[1] = "/home/rhakh/Corewar/test_live.s";
 *
 *
 */