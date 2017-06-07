/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 21:10:34 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/30 21:10:35 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int nb, int power)
{
	if ((nb == 0) && (power == 0))
		return (1);
	if (nb == 0)
		return (0);
	else if (power < 0)
		return (0);
	else if (power > 0)
		return (nb * ft_power(nb, power - 1));
	else
		return (1);
}
