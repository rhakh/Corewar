/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 13:30:32 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/27 13:30:32 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_lowint(void)
{
	char			*low_int;
	char			*res;
	size_t			i;

	i = 0;
	low_int = "-2147483648";
	if ((res = (char *)malloc(sizeof(char) * 12)) == NULL)
		return (NULL);
	while (low_int[i])
	{
		res[i] = low_int[i];
		i++;
	}
	res[11] = '\0';
	return (res);
}

static void			ft_itoch(int n, char *str, int *i)
{
	if (n < 0)
	{
		str[*i] = '-';
		(*i)++;
		n = -n;
	}
	if (n >= 10)
	{
		ft_itoch(n / 10, str, i);
		ft_itoch(n % 10, str, i);
	}
	else
	{
		str[*i] = n + '0';
		(*i)++;
	}
}

static size_t		ft_numnum(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	char			*res;
	int				i;

	if (n == -2147483648)
		return (ft_lowint());
	(res = (char *)malloc(sizeof(char) * 2));
	if (n == 0 && (res != NULL))
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	else if (res == NULL)
		return (NULL);
	if ((res = (char *)malloc(sizeof(char) * (ft_numnum(n) + 1))) == NULL)
		return (NULL);
	ft_bzero(res, ft_numnum(n) + 1);
	i = 0;
	ft_itoch(n, res, &i);
	res[i] = '\0';
	return (res);
}
