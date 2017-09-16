# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhakh <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 15:15:42 by rhakh             #+#    #+#              #
#    Updated: 2017/09/03 13:42:36 by rhakh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = my_vm

SRC =   args_functions.c \
        bcode_functions.c \
        bots_functions.c \
        check_live_bots.c \
        commands_manager.c \
        commands.c \
        flags_parser.c \
        initialization.c \
        ld_functions.c \
        ncurses_creator_win.c \
        ncurses_display_debug.c \
        ncurses_display_memory.c \
        ncurses_display_stats.c \
        ncurses_display_winner.c \
        ncurses_infinit_cycle.c \
        ncurses_init.c \
        ncurses_move.c \
        ncurses_print.c \
        ncurses_windows.c \
        op.c \
        pause_time.c \
        pc_adder.c \
        sdl.c \
        st_functions.c \
        usage.c \
        validate_bots.c \
        vm.c \


SRCDIR = ./

OBJDIR = ../obj_vm/

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

FLAGS = -I ~/Library/Frameworks/Headers -Wall -Wextra -Werror

all: obj $(NAME)

obj:
	make -C ../new_libft all
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) ../new_libft/libft.a -lncurses -I ~/Library/Frameworks/Headers -F/Library/Frameworks -framework SDL2

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
