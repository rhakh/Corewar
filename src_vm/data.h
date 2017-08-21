#ifndef DATA_H
#define DATA_H

# include "op.h"
# include "../new_libft/srcs/libft.h"

typedef struct		s_bot
{
	char			*name;
	char			*comment;
	int				size;
	int				number;
	int				reg[REG_NUMBER + 1];
	int				carry;
	int				pc;
	int				pause_time;
	t_string		*code;
	int 			prev_curr_live[2];
}					t_bot;

/*
** c_to_die means cycles to die
** bot_score[bot_number] <- here will be stored bot's score bu its number
*/
typedef struct		s_data
{
	unsigned char	map[MEM_SIZE];
	int				bot_score[MAX_PLAYERS + 1];
	int				cycles_to_die;
	int 			cycles;
	t_linked_list	*bots;
	int				bots_count;
	int				one_command_mode;
	int				pause;
	size_t			dump;
	char			*players[MAX_PLAYERS + 1];
	char			visual;
}					t_data;

typedef struct		s_op
{
	char			*name;
	int				n_arg;
	char			type_arg[3];
	char			command_number;
	int				cycles_to_done;
	char			*description;
	char			have_opcode;
	char			dir_as_label;
}					t_op;

extern t_op			op_tab[17];

#endif
