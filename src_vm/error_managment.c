/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 13:54:42 by apalanic          #+#    #+#             */
/*   Updated: 2017/08/06 13:54:44 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Error's list
** -1 Failed to open
** -2 Failed to read file
** -3 Failed to close file
** -4
** -5
** -6
** -7
** -8
** -9
** -10
** -11
** -12
** -13
** -14
** -15
** -16
** -17
** -18
** -19
** -20
** -21
*/

static void	errors(int err)
{
	if (err == 1)
		ft_putstr_fd("\x1b[31m[Failed to open]\x1b[0m\n", 2);
	else if (err == 2)
		ft_putstr_fd("\x1b[31m[Failed to read file]\x1b[0m\n", 2);
	else if (err == 3)
		ft_putstr_fd("\x1b[31m[Failed to close file]\x1b[0m\n", 2);
	else if (err == 4)
		ft_putstr_fd("\x1b[31m[Wrong Corewar Exec Magic]\x1b[0m\n", 2);
	else if (err == 5)
		ft_putstr_fd("\x1b[31m[Incorrect Name Chars]\x1b[0m\n", 2);
	else if (err == 6)
		ft_putstr_fd("\x1b[31m[Player size too big]\x1b[0m\n", 2);
	else if (err == 7)
		ft_putstr_fd("\x1b[31m[Wrong int value]\x1b[0m\n", 2);
	else if (err == 8)
		ft_putstr_fd("\x1b[31m[Too many players]\x1b[0m\n", 2);
	else if (err == 9)
		ft_putstr_fd("\x1b[31m[Duplicate player number]\x1b[0m\n", 2);
	else if (err == 10)
		ft_putstr_fd("\x1b[31m[Incorrect comment chars]\x1b[0m\n", 2);
	else
		ft_putstr_fd("\x1b[31m[UNEXPECTED ERROR CODE 1]\x1b[0m\n", 2);
	exit(1);
}

static void	errors2(int err)
{
	if (err == 11)
		ft_putstr_fd("\x1b[31m[Too few arguments for -dump]\x1b[0m\n", 2);
	else if (err == 12)
		ft_putstr_fd("\x1b[31m[-dump value is larger than int max]\x1b[0m\n", 2);
	else if (err == 13)
		ft_putstr_fd("\x1b[31m[Too few arguments for -n flag]\x1b[0m\n", 2);
	else if (err == 14)
		ft_putstr_fd("\x1b[31m[Non numerical chars in numb input]\x1b[0m\n", 2);
	else if (err == 15)
		ft_putstr_fd("\x1b[31m[Wrong int value for -n flag]\x1b[0m\n", 2);
	else if (err == 16)
		ft_putstr_fd("\x1b[31m[Wrong file type. Use: .cor]\x1b[0m\n", 2);
	else if (err == 17)
		ft_putstr_fd("\x1b[31m[The file size is too large.]\x1b[0m ", 2);
	else if (err == 18)
		ft_putstr_fd("\x1b[31m[Too few arguments for -v flag]\x1b[0m\n", 2);
	else if (err == 19)
		ft_putstr_fd("\x1b[31m[Wrong int value for -dump flag]\x1b[0m\n", 2);
	else if (err == 20)
		ft_putstr_fd("\x1b[31m[Incorrect comment chars]\x1b[0m\n", 2);
	else if (err == 21)
		ft_putstr_fd("\x1b[31m[Use only -n [1...4] [bot]]\x1b[0m\n", 2);
	else
		ft_putstr_fd("\x1b[31m[UNEXPECTED ERROR CODE 2]\x1b[0m\n", 2);
	exit(1);
}

void		exit_error(t_data *data, int error_code)
{
//	clean_data(data);			// todo free all memory
	if (error_code < 11)
		errors(error_code);
	else
		errors2(error_code);
}
