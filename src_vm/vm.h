#ifndef VM_H
# define VM_H

# include "op.h"
# include "../new_libft/srcs/libft.h"

typedef struct		s_bot
{
	char 			*name;
	char 			*comment;
	char 			bot_number;
	unsigned 		(r : REG_SIZE)[REG_NUMBER + 1];
	int 			carry;
	int 			pc;
	int 			pause_time;
	t_string		*code;
}					t_bot;

/*
** c_to_die means cycles to die
** bot_score[bot_number] <- here will be stored bot's score bu its number
*/
typedef struct		s_data
{
	unsigned char	map[MEM_SIZE];
	int 			bot_score[MAX_PLAYERS];
	int 			c_to_die;
	t_linked_list	*bots;
}					t_data;

t_bot		*bot_new(int number, t_string *code);
void 		bot_del(t_bot **bot);

int 		read_bot(t_string *code, char *file_name);
int 		validate_bots(t_data *data);

#endif
