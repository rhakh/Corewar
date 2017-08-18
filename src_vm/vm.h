#ifndef VM_H
# define VM_H

# include "op.h"
# include <fcntl.h>
# include <ncurses.h>
# include "../new_libft/srcs/libft.h"

typedef struct		s_bot
{
	char 			*name;
	char 			*comment;
	int 			size;
	int 			number;
	int				reg[REG_NUMBER + 1];
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
	int 			bots_count;
	int 			one_command_mode;
	int 			pause;

	size_t			dump;					// apalanic: dump value use if only  dump > 0
	char			*players[MAX_PLAYERS + 1]; // apalanic: list of arguments -- needs free()
	char 			visual;
}					t_data;

typedef struct 			s_op
{
	char 				*name;
	int 				n_arg;
	char 				type_arg[3];
	char 				command_number;
	int 				cycles_to_done;
	char 				*description;
	char 				have_opcode;
	char 				dir_as_label;
}						t_op;

extern t_op    			op_tab[17];

# include "args_functions.h"
# include "commands.h"
# include "flags_parser.h"

t_bot			*bot_new(int number, t_string *code);
void 			bot_del(t_bot **bot);

int 			read_bot(t_string *code, char *file_name);
int 			validate_bots(t_data *data);
void			ft_display_arena(t_data *data);
WINDOW			*create_newwin(int height, int width, int starty, int startx);
int 			read_bot(t_string *code, char *file_name);
int 			validate_bots(t_data *data);
void			print_bcode(const char *code, int len);
int 			get_number_from_bcode(const unsigned char *code, int num_size);
int 			put_number_to_bcode(t_data *data, int num, int position);
int 			send_to_ncurses(int start, int len, t_bot *bot, t_data *data);

#endif
