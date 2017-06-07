/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 22:04:18 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/24 22:04:20 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_colour(t_strp *res, char **s)
{
	if (!(ft_strncmp(*s, "{red}", 5)) && (*s += 5))
		put_str_to_strp(res, RED);
	else if (!(ft_strncmp(*s, "{green}", 7)) && (*s += 7))
		put_str_to_strp(res, GREEN);
	else if (!(ft_strncmp(*s, "{yellow}", 8)) && (*s += 8))
		put_str_to_strp(res, YELLOW);
	else if (!(ft_strncmp(*s, "{blue}", 6)) && (*s += 6))
		put_str_to_strp(res, BLUE);
	else if (!(ft_strncmp(*s, "{magenta}", 9)) && (*s += 9))
		put_str_to_strp(res, MAGENTA);
	else if (!(ft_strncmp(*s, "{cyan}", 6)) && (*s += 6))
		put_str_to_strp(res, CYAN);
	else if (!(ft_strncmp(*s, "{white}", 7)) && (*s += 7))
		put_str_to_strp(res, WHITE);
	else if (!(ft_strncmp(*s, "{eoc}", 5)) && (*s += 5))
		put_str_to_strp(res, EOC);
	else
		return (0);
	return (1);
}
