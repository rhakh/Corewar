# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhakh <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 15:15:42 by rhakh             #+#    #+#              #
#    Updated: 2017/03/08 19:30:14 by rhakh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = my_asm

SRC =   array_string.c \
        bcode.c \
        check_bot_params.c \
        create_command.c \
        data_constructor.c \
        error_messenger.c \
        get_arg.c \
        get_args_type.c \
        get_op_code.c \
        helpers.c \
        label_table.c \
        lex_analyze.c \
        linked_list.c \
        main.c \
        op.c \
        put_label.c \
        split_line.c \
        syntax_analyze.c \
        write_bcode.c \

SRCDIR = ./src_asm/

OBJDIR = ./obj_asm/

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

FLAGS = -Wall -Wextra -Werror

all: obj $(NAME)

obj:
	make -C ./new_libft all
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) ./new_libft/libft.a

clean:
	make -C ./new_libft clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C ./new_libft fclean
	/bin/rm -f $(NAME)

re: fclean all
