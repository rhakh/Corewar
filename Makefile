# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhakh <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/28 15:15:42 by rhakh             #+#    #+#              #
#    Updated: 2017/08/13 12:16:54 by sbondar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C new_libft all
	make -C src_asm all
	make -C src_vm all

clean:
	make -C src_asm clean
	make -C src_vm clean

fclean: clean
	make -C src_asm fclean
	make -C src_vm fclean

re: fclean all

corewar:
	make -C src_vm all

asm:
	make -C src_asm all

libft:
	make -C new_libft all

config:
	sudo apt-get install libncurses5-dev pkg-config libsdl2-dev
