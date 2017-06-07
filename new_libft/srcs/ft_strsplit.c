/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 13:04:54 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/26 13:04:54 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_wdlen(const char *s, char c)
{
	size_t			size;

	size = 0;
	while (s[size] != '\0' && s[size] != c)
		size++;
	return (size);
}

static size_t		ft_countwd(const char *s, char c)
{
	size_t			i;
	size_t			wd_count;

	i = 0;
	wd_count = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c) && s[i] != '\0')
			i++;
		if (s[i])
			wd_count++;
		while (!(s[i] == c) && s[i] != '\0')
			i++;
	}
	return (wd_count);
}

static char			*ft_paswd(const char *s, size_t wd_length)
{
	char			*word;
	size_t			i;

	i = 0;
	if ((word = (char *)malloc(sizeof(char) * (wd_length + 1))) == NULL)
		return (NULL);
	while (i < wd_length)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**arr;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (ft_countwd(s, c) + 1))))
		return (NULL);
	while (i < ft_countwd(s, c))
	{
		while ((s[j] == c))
			j++;
		if ((arr[i] = ft_paswd(s + j, ft_wdlen(s + j, c))) == NULL)
			return (NULL);
		while (s[j] != c && s[j])
			j++;
		i++;
	}
	arr[i] = 0;
	return (arr);
}
