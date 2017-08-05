#include "../new_libft/srcs/libft.h"
#include "vm.h"

/*
** 0 - ok, 1 - error
*/
int 		infinit_loop(t_data *data)
{
	//todo:hakh execute bots commands
	//todo:bondar synchronized output using opengl
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		init_bots(t_data *data)
{
	//todo:hakh write bots code to t_string, validate it, load into map
	return (0);
}

int         main(int argc, char **argv)
{
	t_data	data;

	//todo:palanich process arguments and return ordered array of bots names
	//todo:hakh
	if (init_bots(&data))
		return (1);
	if (infinit_loop(&data))
		return (1);
	//todo: calculate winner

	//todo:hakh free bots code (t_string)
	ft_printf ("%d, %s", argc, argv[0]);
}
