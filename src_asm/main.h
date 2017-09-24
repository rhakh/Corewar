/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:43:10 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:43:11 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "op.h"
# include "../new_libft/srcs/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define CORRECT_CHARS	"abcdefghijklmnopqrstuvwxyz_-+0123456789"

typedef struct		s_data
{
	char				**arr;
	int					i;
	size_t				size;
}					t_data;

typedef struct		s_array_string
{
	char				**arr;
	int					i;
	size_t				size;
}					t_array_string;

typedef struct		s_label_table
{
	char				*link;
	int					offset;
	void				*next;
}					t_label_table;

typedef struct		s_bcode
{
	char				*oper_number;
	char				*op_code;
	char				*arg_type;
	int					*args;
	void				*next;
}					t_bcode;

typedef struct		s_put_label
{
	char				*name;
	int					*arg;
	int					curr_pc;
	void				(* print_put_label)();
	void				(* del_put_label)();
}					t_put_label;

typedef struct		s_main
{
	t_data				*code;
	t_linked_list		*lex_strings;
	t_label_table		*table;
	t_bcode				*bcode;
	t_linked_list		*list;
	int					errors;
	int					pc;
	char				name[PROG_NAME_LENGTH];
	char				comment[COMMENT_LENGTH];
	int					name_exist;
	int					comm_exist;
}					t_main;

typedef struct		s_op
{
	char				*name;
	int					n_arg;
	char				type_arg[3];
	char				command_number;
	int					cycles_to_done;
	char				*description;
	char				have_opcode;
	char				dir_as_label;
}					t_op;

extern t_op			g_tab[17];

/*
**	array_string.c
*/

t_array_string		*new_array_string(size_t size);
void				del_array_string(t_array_string **arr);
int					add_str_to_array_string(t_array_string *arr, char *str);
void				print_array_string(t_array_string *arr);
void				print_string(t_array_string *arr);

/*
**	split_line.c
*/

t_array_string		*split_line(char *code);

/*
**	data_constructor.c
*/

void				del_all_data(t_data **data);
void				del_data(t_data *data);
t_data				*new_data(size_t size);
void				print_data(t_data *data);
void				read_data(int fd, t_data **data);

/*
** lex_analyze.c
*/

t_linked_list		*lex_analyze(t_main *main, t_data *code);
void				print_lex(t_linked_list *lex_strs);
void				del_lex_strs(t_linked_list *lex_strs);
int					is_comment(char *str);

/*
** syntax_analyze.c
*/

void				syntax_analyze(t_main *main);

/*
** label_table.c
*/

t_label_table		*new_label_table(char *name, int offset);
void				del_label_table(t_label_table **table);
void				print_label_table(t_label_table *table);
void				add_label_to_table(t_label_table **table,
					t_label_table *label);
t_label_table		*find_label_by_name(t_label_table *table, char *name);

/*
** bcode.c
*/

t_bcode				*new_bcode(char op, char op_code[3], int *args);
void				del_bcode(t_bcode **bcode);
void				print_bcode(t_bcode *bcode);
void				add_bcode(t_bcode **table, t_bcode *code);

/*
** create_command.c
*/

void				create_command(t_main *main, t_array_string *lex_str);

/*
** is_number.c
*/

int					is_number(const char *str);
int					is_empty_line(const char *str);
int					is_link(const char *str);
int					is_register(const char *str);
int					is_command(const char *str);
int					is_printable(int c);

/*
** get_op_code.c
*/

char				get_op_code(char arg_type[3]);

/*
** get_arg_type.c
*/

int					get_args_type(t_array_string *lex_str, char arg_type[3],
					int i, int pair_bit);
int					get_arg(t_main *main, t_array_string *lex_str, int *i,
					int *arg);

/*
** error_messenger.c
*/

void				print_error(char *message, t_array_string *lex_str);
void				print_syntax_error(char *message, t_array_string *lex_str,
					t_main *main);
void				print_syntax_error_label(char *message, char *label_name,
					t_main *main);
void				init_create_command(int *i, int **args, char arg_type[3],
					t_array_string *lex_str);

/*
** get_arg.c
*/

int					get_arg(t_main *main, t_array_string *lex_str, int *i,
					int *arg);
void				write_args(int fd, t_bcode *curr);
void				write_one_arg(int fd, unsigned int arg, int i);

/*
** put_label.c
*/

t_put_label			*new_put_label(char *name_label, int *arg, int curr_pc);
void				del_put_label(t_put_label **put_label);

/*
** write_bcode.c
*/

void				write_bcode(char *src_name, t_main *main);

/*
** check_bot_params.c
*/

int					check_bot_params(char *name, char *comment, char *str);

#endif
