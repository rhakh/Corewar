#include "main.h"

int 	main(int argc, char **argv)
{
	t_data			*code;
	t_array_string	**lex_strings;
	int 			fd;

//	argv[1] = "/home/rhakh/Corewar/champs/jumper.s";
    argv[1] = "/nfs/2016/r/rhakh/Corewar/champs/jumper.s";
    argv[1] = "/nfs/2016/r/rhakh/Corewar/test_live.s";
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
	code = new_data(30);
	read_data(fd, &code);
	print_data(code);

	lex_strings = lex_analyze(code);
	print_lex(lex_strings);

	syntax_analyze(lex_strings);

	del_lex_strs(&lex_strings);
	del_all_data(&code);
	close(fd);
	return (0);
}

//todo trim input string
//todo recode is_link
/*
 * argv[1] = "/home/rhakh/Corewar/test_live.s";
 *
 *
 */