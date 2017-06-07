/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 21:46:30 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/21 21:46:31 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	size_src;
	size_t	i;

	i = 0;
	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	if (size_dst + 1 > size)
		return (size + size_src);
	else
	{
		while ((src[i] != '\0') && (size_dst + i + 1 < size))
		{
			dst[size_dst + i] = src[i];
			i++;
		}
		dst[size_dst + i] = '\0';
	}
	return (size_dst + size_src);
}
