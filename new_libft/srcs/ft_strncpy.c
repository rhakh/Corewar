/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 20:20:51 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/21 20:20:55 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	size_src;
	size_t	i;

	i = 0;
	size_src = ft_strlen(src);
	while (i < size_src && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	if (size_src < len)
		while (i < len)
			dst[i++] = '\0';
	return (dst);
}
