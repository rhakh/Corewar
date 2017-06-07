/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 20:28:28 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/30 20:28:29 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memdup(const void *src, size_t n)
{
	void		*dst;

	if (((dst = malloc(n)) == NULL) || src == NULL)
		return (NULL);
	ft_memcpy(dst, src, n);
	return (dst);
}
