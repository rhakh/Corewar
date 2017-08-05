#include "vm.h"

t_bot		*bot_new(int number, t_string *code)
{
	t_bot	*bot;

	if ((bot = (t_bot *)malloc(sizeof(t_bot))) == NULL)
		return (NULL);
	ft_bzero(bot, sizeof(t_bot));
	return (bot);
}

void		bot_del(t_bot **pbot)
{
	t_bot	*bot;

	if (pbot && *pbot)
	{
		bot = *pbot;
		if (bot->name)
			free(bot->name);
		if (bot->comment)
			free(bot->comment);
		if (bot->code)
			string_del(&(bot->code));
		*pbot = NULL;
	}
}

int 		read_bot(t_string *code, char *file_name)
{
	int		fd;
	int 	len;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	ft_bzero(buff, BUFF_SIZE + 1);
	if (fd > 0)
	{
		while ((len = (int)read(fd, buff, BUFF_SIZE)) > 0)
		{
			string_append(code, buff, len);
			ft_bzero(buff, len + 1);
		}
		if (len == 0)
			return (0);
		else
			return (1);
	}
	return (1);
}

int 		get_number_from_bcode(const unsigned char *code, int num_size)
{
	int 			i;
	int 			num;
	unsigned char	*pnum;

	num = 0;
	pnum = &num + sizeof(int) - 1;
	i = -1;
	while (++i && i < num_size)
	{
		*pnum = *code;
		code++;
		pnum--;
	}
	return (num);
}

int 		validate_magic_number(t_bot *bot)
{
	int 	mag_num;

	mag_num = get_number_from_bcode((const unsigned char *)bot->code->str, sizeof(int));
	if (mag_num == COREWAR_EXEC_MAGIC)
		return (0);
	return (1);
}

int 		validate_bot_size(t_bot *bot)
{

}

/*
** 0 - ok, 1 - error
*/
int 		validate_bots(t_data *data)
{
	t_linked_list	*curr;

	curr = data->bots;
	while (curr)
	{
		if (validate_magic_number(curr->data))
			return (1);
		if (validate_bot_size(curr->data))
			return (1);
	}
	return (0);
}