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
		while ((len = read(fd, buff, BUFF_SIZE)) > 0)
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

int 		validate_bots(t_data *data)
{

}