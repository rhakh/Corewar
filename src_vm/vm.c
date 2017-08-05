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
int 		init_bots(t_data *data, char **argv)
{
	//todo:hakh write bots code to t_string, validate it, load into map
	int 		i;
	int 		ret;
	t_string	*curr;
	t_bot		*bot;

	i = -1;
	ret = 0;
	while (++i && i < MAX_PLAYERS)
	{
		curr = string_new(30);
		(read_bot(curr, argv[i])) ? (ret = 1) : 0;
		(bot_new(i + 1, curr)) ? (ret = 1) : 0;
		if (ret)
		{
			list_del(&(data->bots), bot_del);
			string_del(&curr);
			return (1);
		}
		list_push_back(&(data->bots), bot);
	}
	if (validate_bots(data))
	{
		list_del(&(data->bots), bot_del);
		return (1);
	}
	return (0);
}

int         main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	//todo:palanich process arguments and return ordered array of bots names
	//todo:hakh
	if (init_bots(&data, argv))
		return (1);
	if (infinit_loop(&data))
		return (1);
	//todo: calculate winner

	//todo:hakh free bots code (t_string)
	ft_printf ("%d, %s", argc, argv[0]);
}
