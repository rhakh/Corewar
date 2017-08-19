# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhakh <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 15:15:42 by rhakh             #+#    #+#              #
#    Updated: 2017/08/13 12:22:39 by sbondar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = my_vm

SRC =   vm.c \
        bots_functions.c \
        init_ncurses.c \
        ncurses_windows.c \
        ncurses_move.c \
        op.c \
        args_functions.c \
        commands.c \
        add_players.c \
        error_managment.c \
        flags_parser.c \
        usage.c \
        creator_win.c \
        display_memory.c \

SRCDIR = ./

OBJDIR = ../obj_vm/

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

FLAGS = #-Wall -Wextra -Werror

all: obj $(NAME)

obj:
	make -C ../new_libft all
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) ../new_libft/libft.a -lncurses

clean:
	make -C ../new_libft clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C ../new_libft fclean
	/bin/rm -f $(NAME)

re: fclean all
