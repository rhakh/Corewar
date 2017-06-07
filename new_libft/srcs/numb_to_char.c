/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numb_to_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:58:45 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:58:47 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			llpaste_in_str(long long num, int base, char *str, int *i)
{
	char		*mask;

	mask = "0123456789abcdef";
	if (num <= -base || num >= base)
		llpaste_in_str(num / base, base, str, i);
	str[(*i)++] = mask[ABS(num % base)];
}

char			*lltoa_base(long long num, int base)
{
	char		*str;
	int			i;

	i = 0;
	if ((str = ft_strnew(65)) == NULL)
		return (NULL);
	if (base >= 2 && base <= 16)
		llpaste_in_str(num, base, str, &i);
	else
		return (NULL);
	str[i] = 0;
	return (str);
}

void			ullpaste_in_str(unsigned long long num, int base,
								char *str, int *i)
{
	char		*mask;

	mask = "0123456789abcdef";
	if (num >= (unsigned int)base)
		ullpaste_in_str(num / base, base, str, i);
	str[(*i)++] = mask[num % base];
}

char			*ulltoa_base(unsigned long long num, int base)
{
	char		*str;
	int			i;

	i = 0;
	if ((str = ft_strnew(65)) == NULL)
		return (NULL);
	if (base >= 2 && base <= 16)
		ullpaste_in_str(num, base, str, &i);
	else
		return (NULL);
	str[i] = 0;
	return (str);
}
