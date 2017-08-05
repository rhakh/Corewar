#ifndef VM_H
# define VM_H

# include "op.h"

typedef struct		s_bot
{
	char 			*name;
	char 			bot_number;
	int 			r[REG_NUMBER];
	int 			carry;
	int 			pc;
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

t_bot		*bot_new(const char *name, int number);
void 		bot_del(t_bot **bot);


#endif
