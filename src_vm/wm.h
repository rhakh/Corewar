/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:05:17 by apalanic          #+#    #+#             */
/*   Updated: 2017/08/06 12:05:19 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <fcntl.h>
# include "op.h"
# include "./new_libft/srcs/libft.h"

typedef struct		s_bot
{
	char 			*name;
	char 			*comment;
	char 			bot_number;
//	unsigned 		(r : REG_SIZE)[REG_NUMBER + 1];
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
	size_t			bot_cnt;				// apalanic: count bots and compare to MAX_PLAYERS
	size_t			dump;					// apalanic: dump value use if only  dump > 0
	char			*players[MAX_PLAYERS + 1];				// apalanic: list of arguments -- needs free()
	int 			visual;
}					t_data;

t_bot		*bot_new(int number, t_string *code);
void 		bot_del(t_bot **bot);

int 		read_bot(t_string *code, char *file_name);
int 		validate_bots(t_data *data);

// apalanic
void		exit_error(t_data *data, int error_code);
void		usage(void);
void		add_wn(t_data *data, int *i, char **argv, int argc);
void		add_player(t_data *data, int *i, char **argv, int argc);
void		parse_flags(t_data *data, int argc, char **argv);
void	print(t_data *data);		//tmp
#endif

