#include "vm.h"

t_bot		*bot_new(int number, t_string *code)
{
	t_bot	*bot;

	if ((bot = (t_bot *)malloc(sizeof(t_bot))) == NULL)
	{
		ft_printf("Can't allocate memory");
		return (NULL);
	}
	ft_bzero(bot, sizeof(t_bot));
	bot->code = code;
	bot->number = number;
	bot->pause_time = 0;
	bot->last_live = 0;
	bot->live_count = 0;
	bot->prev_st = -1;
	bot->prev_live = -1;
	bot->prev_attr = -1;
	return (bot);
}

t_bot		*bot_copy(t_bot *src)
{
	t_bot	*dst;

	if ((dst = bot_new(src->number, NULL)) == NULL)
		return (NULL);
	dst->number = src->number;
	dst->r1_number = src->r1_number;
	dst->pc = src->pc;
	dst->pause_time = src->pause_time;
	dst->prev_live = src->prev_live;
	dst->prev_st = src->prev_st;
	dst->prev_attr = src->prev_attr;
	ft_memcpy(dst->reg, src->reg, (REG_NUMBER + 1) * sizeof(int));
	dst->throw_live = src->throw_live;
	dst->carry = src->carry;
	dst->is_dead = src->is_dead;
	dst->last_live = src->last_live;
	dst->live_count = 0;
	dst->size = src->size;
	dst->start = src->start;
	return (dst);
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
		free(bot);
		*pbot = NULL;
	}
}

void		bots_list_del(t_linked_list **head)
{
	t_linked_list		*curr;
	t_linked_list		*next;

	if (head != NULL)
		curr = *head;
	else
		return ;
	if (curr != NULL)
	{
		next = curr;
		while (next != NULL)
		{
			if (curr != NULL)
			{
				next = curr->next;
				bot_del((t_bot **)&(curr->data));
				curr->data = NULL;
				curr->next = NULL;
				free(curr);
				curr = next;
			}
		}
		*head = NULL;
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
		{
			ft_printf("Read error\n");
			return (1);
		}
	}
	ft_printf("{red}Can't open file '%s'{eoc}\n", file_name);
	return (1);
}

int 		get_number_from_bcode(const unsigned char *code, int num_size)
{
	int 			i;
	int 			num;
	unsigned char	*pnum;

	num = 0;
	pnum = (unsigned char *)(&num);
	i = 0;
	code += num_size - 1;
	while (i < num_size)
	{
		*pnum = *code;
		code--;
		pnum++;
		i++;
	}
	return ((num_size == 2) ? ((short)num) : (num));
}

int 		put_number_to_bcode(t_data *data, int num, int position)
{
	int 			i;
	unsigned char	*pnum;

	i = 0;
	pnum = (unsigned  char *)&num;
	position += 3;
	while (i < DIR_SIZE)
	{
		*(data->map + ((position + MEM_SIZE) % MEM_SIZE)) = *pnum;
		i++;
		pnum++;
		position--;
	}
	return (0);
}

int 		validate_magic_number(t_bot *bot)
{
	int 	mag_num;

	mag_num = get_number_from_bcode(
			(const unsigned char *)bot->code->str,
			sizeof(int));
	if (mag_num == COREWAR_EXEC_MAGIC)
		return (0);
	ft_printf("Incorrect magic number\n");
	return (1);
}

int 			validate_bot_size(t_bot *bot)
{
	int		size1;
	int 	size2;

	size1 = get_number_from_bcode((unsigned char *)
						bot->code->str + 8 + PROG_NAME_LENGTH, sizeof(int));
	size2 = (int)bot->code->len - sizeof(int) -
						PROG_NAME_LENGTH - 12 - COMMENT_LENGTH;
	if (size1 != size2)
	{
		ft_printf("{red}Error:{eoc} declared and actual size are"
						  "not equal %d != %d\n", size1, size2);
		return (1);
	}
	if (size1 > CHAMP_MAX_SIZE)
	{
		ft_printf("{red}Error:{eoc} champ size is too big, "
						  "max size = %d\n", CHAMP_MAX_SIZE);
		return (1);
	}
	bot->size = size1;
	return (0);
}

/*
** 0 - ok, 1 - error
*/
int 		validate_bots(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*curr_bot;
	int				i;

	i = 1;
	curr = data->bots;
	while (curr)
	{
		curr_bot = (t_bot *)curr->data;
		if (validate_magic_number(curr_bot))
			return (1);
		if (validate_bot_size(curr_bot))
			return (1);
		curr_bot->name = ft_strndup(curr_bot->code->str +
											sizeof(int), PROG_NAME_LENGTH);
		curr_bot->comment = ft_strndup(curr_bot->code->str +
			sizeof(int) + PROG_NAME_LENGTH + 4 + sizeof(int), COMMENT_LENGTH);
		ft_memcpy(data->bots_names[i], curr_bot->name,
				  ft_strlen(curr_bot->name));
		i++;
		curr = curr->next;
	}
	return (0);
}