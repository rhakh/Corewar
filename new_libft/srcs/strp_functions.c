/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:59:19 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:59:21 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_strp		*new_strp(size_t size)
{
	t_strp	*res;

	if ((res = (t_strp *)malloc(sizeof(t_strp))) == NULL)
		return (NULL);
	if ((res->str = ft_strnew(size)) == NULL)
		return (NULL);
	res->i = 0;
	res->last_size = size;
	return (res);
}

void		del_strp(t_strp **t)
{
	free((*t)->str);
	(*t)->str = NULL;
	free(*t);
	*t = NULL;
}

int			put_char_to_strp(t_strp *res, char c)
{
	if (res->i + 1 >= res->last_size)
		while ((realloc_strp(res) == 0) || (res->last_size < res->i + 1))
			;
	*(res->str + res->i) = c;
	res->i++;
	return (1);
}

int			put_strp_to_strp(t_strp *dst, t_strp *src)
{
	if (dst->i + src->i >= dst->last_size)
		while ((realloc_strp(dst) == 0) || (dst->last_size < src->i))
			;
	ft_memcpy(dst->str + dst->i, src->str, (size_t)src->i);
	dst->i += src->i;
	return (1);
}

int			put_str_to_strp(t_strp *res, char *str)
{
	if (res->i + (int)ft_strlen(str) >= res->last_size)
		while ((realloc_strp(res) == 0) || (res->last_size < ft_strlen(str)))
			;
	if (str == NULL)
		put_str_to_strp(res, "(null)");
	else
	{
		ft_memcpy(res->str + res->i, str, ft_strlen(str));
		res->i += ft_strlen(str);
	}
	return (1);
}
