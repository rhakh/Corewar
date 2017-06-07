/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:22:50 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/22 17:22:51 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *litt, size_t l)
{
	size_t	i;
	size_t	j;

	if (*litt == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < l)
	{
		j = 0;
		while (big[i + j] == litt[j] && big[i + j] != '\0' && i + j < l)
		{
			if (litt[j + 1] == '\0')
				return ((char *)(big + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
