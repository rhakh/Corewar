#ifndef MAIN_H
#define MAIN_H

#include "op.h"
#include "../new_libft/srcs/libft.h"
#include <fcntl.h>

typedef struct			s_data
{
	char				**arr;
	int					i;
	size_t				size;
}						t_data;

typedef struct			s_array_string
{
	char 				**arr;
	int 				i;				//str count
	size_t 				size;
}						t_array_string;

typedef struct			s_label_table
{
	char 				*link;
	int 				offset;
	void				*next;
}						t_label_table;

typedef struct			s_bcode
{
	char 				*oper_number;
	char 				*op_code;
	char 				*arg_type;
	int 				*args;
	void				*next;
}						t_bcode;

typedef struct			s_put_label
{
	char 				*name;
	int 				*arg;
	int 				curr_pc;
	void				(* print_put_label)();
	void				(* del_put_label)();
}						t_put_label;

typedef struct 			s_linked_list
{
	void 				*data;
	void				*next;
}						t_linked_list;

typedef struct			s_main
{
	t_data				*code;
	t_array_string		**lex_strings;
	t_label_table		*table;
	t_bcode				*bcode;
	t_linked_list		*list;
	int 				errors;
	int 				pc;
	char 				name[PROG_NAME_LENGTH];
	char 				comment[COMMENT_LENGTH];
}						t_main;

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

extern t_op    op_tab[17];//[17] =
//{
//		{"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0},
//		{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0},
//		{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0},
//		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
//		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
//		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
//		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
//		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
//		{"zjmp", 1, {T_DIR, 0 , 0}, 9, 20, "jump if zero", 0, 1},
//		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
//		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
//		{"fork", 1, {T_DIR, 0 , 0}, 12, 800, "fork", 0, 1},
//		{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, "long load", 1, 0},
//		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
//		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
//		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
//		{0, 0, {0}, 0, 0, 0, 0, 0}
//};

//typedef enum e_op
//{
//	live = 1, ld, st, add ,sub, and, or, xor, zjmp,
//	ldi, sti, _fork, lld, lldi, lfork, aff
//};

/*
**	array_string.c
*/
t_array_string	*new_array_string(size_t size);
int				realloc_array_string(t_array_string **arr);
void			del_array_string(t_array_string **arr);
int 			add_str_to_array_string(t_array_string *arr, char *str);
void 			print_array_string(t_array_string *arr);
void			print_string(t_array_string *arr);

/*
**	split_line.c
*/
t_array_string	*split_line(char *code);

/*
**	data_constructor.c
*/
void		realloc_data(t_data **src);
void		del_all_data(t_data **data);
void		del_data(t_data *data);
t_data		*new_data(size_t size);
void		print_data(t_data *data);
void		read_data(int fd, t_data **data);

/*
** lex_analyze.c
*/
t_array_string		**lex_analyze(t_data *code);
void				print_lex(t_array_string **lex_strs);
void				del_lex_strs(t_array_string ***str);

/*
** syntax_analyze.c
*/
void		syntax_analyze(t_main *main);

/*
** label_table.c
*/
t_label_table		*new_label_table(char *name, int offset);
void				del_label_table(t_label_table **table);
void				print_label_table(t_label_table *table);
void				add_label_to_table(t_label_table **table, t_label_table *label);
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
* is_number.c
*/
int 				is_number(const char *str);
int 				is_empty_line(const char *str);
int 				is_link(const char *str);
int 				is_register(const char *str);
int 				is_command(const char *str);

/*
** get_op_code.c
*/
char				get_op_code(char arg_type[3]);

/*
** get_arg_type.c
*/
int				get_args_type(t_array_string *lex_str, char arg_type[3], int i, int pair_bit);

/*
** error_messenger.c
*/
void				print_error(char *message, t_array_string *lex_str);
void				print_syntax_error(char *message, t_array_string *lex_str, t_main *main);
void				print_syntax_error_label(char *message, char *label_name, t_main *main);

/*
** get_arg.c
*/
int 				get_arg(t_main *main, t_array_string *lex_str, int *i, int *arg);


/*
** put_label.c
*/
t_put_label			*new_put_label(char *name_label, int *arg, int curr_pc);
void				del_put_label(t_put_label **put_label);

/*
** linked_list.c
*/
t_linked_list	*new_linked_list_elem();
void			linked_list_push_back(t_linked_list **head, void *data);
void			print_linked_list(t_linked_list *curr, void (* print)(void *));
void			del_linked_list(t_linked_list **head, void (* function_for_del_data)(void *));



#endif
