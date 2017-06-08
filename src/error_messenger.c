#include "main.h"

void		print_error(char *message, t_array_string *lex_str)
{
	ft_printf("{red}Error:{eoc} {yellow}%s: {eoc}", message);
	print_string(lex_str);
	ft_printf("\n");
}

void		print_syntax_error(char *message, t_array_string *lex_str, t_main *main)
{
	ft_printf("{red}Error:{eoc} {yellow}%s: {eoc}", message);
	print_string(lex_str);
	ft_printf("\n");
	main->errors++;
}