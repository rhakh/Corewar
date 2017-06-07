/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 12:18:03 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/26 12:18:04 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	char		*res;
	size_t		i;

	if (s == NULL)
		return (NULL);
	while ((*s == ' ' || *s == '\t' || *s == '\n') && *s != '\0')
		s++;
	if ((res = ft_strdup(s)) == NULL)
		return (NULL);
	i = ft_strlen(res) - 1;
	while (res[i] == ' ' || res[i] == '\t' || res[i] == '\n')
	{
		res[i] = '\0';
		i--;
	}
	res = ft_strdup(res);
	return (res);
}
