/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:27:19 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/22 21:27:20 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;
	size_t				i;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if (psrc[i] != (unsigned char)c)
			pdst[i] = (unsigned char)psrc[i];
		else
		{
			pdst[i] = (unsigned char)psrc[i];
			return (dst + i + 1);
		}
		i++;
	}
	return (NULL);
}
