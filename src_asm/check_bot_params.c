/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:03:05 by apalanic          #+#    #+#             */
/*   Updated: 2017/09/13 17:56:58 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int				is_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

static void		dummy_norms(char *dst, int max_len, char *tmp)
{
	ft_bzero(dst, (size_t)max_len);
	ft_strncpy(dst, tmp + 1, (size_t)(ft_strchr(tmp + 1, '"') - (tmp + 1)));
}

/*
** 0 KO, 2 name , 3 comment
*/

int				check_bot_params(char *name, char *comment, char *str)
{
	char	*tmp;
	int		max_len;
	char	*dst;
	int		ret;

	tmp = str;
	max_len = -1;
	while (is_white_space(*tmp))
		tmp++;
	(ft_strncmp(tmp, NAME_CMD_STRING, 5)) ? 0 : (max_len = PROG_NAME_LENGTH);
	(ft_strncmp(tmp, COMMENT_CMD_STRING, 8)) ? 0 : (max_len = COMMENT_LENGTH);
	if (max_len == -1)
		return (0);
	(ft_strncmp(tmp, NAME_CMD_STRING, 5)) ? (dst = comment) :
		(dst = name);
	(ft_strncmp(tmp, NAME_CMD_STRING, 5)) ? (ret = 3) :
		(ret = 2);
	(ft_strncmp(tmp, NAME_CMD_STRING, 5)) ? (tmp += 8) : (tmp += 5);
	while (is_white_space(*tmp))
		tmp++;
	if (*tmp != '"' || !ft_strchr(tmp + 1, '"')
		|| (ft_strchr(tmp + 1, '"') - (tmp + 1)) > max_len)
		return (0);
	dummy_norms(dst, max_len, tmp);
	return (ret);
}

void			print_data(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->i)
	{
		ft_printf("%s\n", data->arr[i]);
		i++;
	}
}
