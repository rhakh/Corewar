/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 10:05:38 by apalanic          #+#    #+#             */
/*   Updated: 2017/08/06 10:05:40 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags_parser.h"

void	usage(void)
{
	ft_putstr_fd("\t** --------------------USAGE--------------------\n\
\t** ./corewar [-h || --help] to view this massege\n \
\t** Example: ./corewar -v -n 3 player.cor\n \
\t** GUI: ./corewar -v [player1.cor player2.cor...]\n \
\t** Default player numbers: 1, 2, 3, 4 [This numbers only for -n\n \
\t** Change player number: -n -[number] player.cor\n \
\t** Dump: ./corewar -dump 50 [Players] -> it will print the memory after \
50 cycles\n", 2);
	exit(1);
}
