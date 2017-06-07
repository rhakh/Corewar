/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:05:50 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/22 21:05:51 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;
	size_t				i;

	i = 0;
	pdst = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (n == 0 || dst == src)
		return (dst);
	while (i < n)
	{
		ft_memset(&pdst[i], psrc[i], 1);
		i++;
	}
	return (dst);
}
