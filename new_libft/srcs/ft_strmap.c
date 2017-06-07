/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:54:25 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/25 14:54:26 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len_s;
	char	*res;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	res = (char *)malloc(len_s + 1);
	if (res == NULL || f == NULL)
		return (NULL);
	len_s = 0;
	while (*s != '\0')
	{
		res[len_s] = f(*s);
		s++;
		len_s++;
	}
	res[len_s] = '\0';
	return (res);
}
