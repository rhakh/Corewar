/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:58:59 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:59:01 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long				cast_num(t_spec *sp, va_list *ap)
{
	long long			n;

	n = va_arg(*ap, long long);
	if (sp->size == hh)
		return ((char)n);
	else if (sp->size == h)
		return ((short)n);
	else if (sp->size == l)
		return ((long)n);
	else if (sp->size == ll)
		return (n);
	else if (sp->size == z)
		return ((ssize_t)n);
	else if (sp->size == j)
		return ((intmax_t)n);
	return ((int)n);
}

unsigned long long		ucast_num(t_spec *sp, va_list *ap)
{
	unsigned long long	n;

	n = va_arg(*ap, unsigned long long);
	if (sp->size == hh)
		return ((unsigned char)n);
	else if (sp->size == h)
		return ((unsigned short)n);
	else if (sp->size == l)
		return ((unsigned long)n);
	else if (sp->size == ll)
		return (n);
	else if (sp->size == z)
		return ((size_t)n);
	else if (sp->size == j)
		return ((uintmax_t)n);
	return ((unsigned int)n);
}

t_strp					*get_prec_num(t_spec *sp, char *number)
{
	t_strp				*num;
	int					i;

	if ((num = new_strp(50)) == NULL)
		return (NULL);
	i = 0;
	if ((number[0] == '0') && (sp->precision == 0))
		return (num);
	if (sp->precision > (int)ft_strlen(number))
		while (i < sp->precision - (int)ft_strlen(number))
		{
			put_char_to_strp(num, '0');
			i++;
		}
	put_str_to_strp(num, number);
	return (num);
}

void					pre_processing(t_spec *sp)
{
	if (sp->conversion >= d && sp->conversion <= X)
	{
		(sp->precision >= 0) ? (sp->flags[zero] = 0) : 0;
		(sp->flags[plus] == 1) ? (sp->flags[space] = 0) : 0;
		if ((sp->h_count % 2 == 0) && (sp->h_count > 0))
			(sp->size < hh) ? (sp->size = hh) : 0;
		else if (sp->h_count > 0)
			(sp->size < h) ? (sp->size = h) : 0;
		if ((sp->l_count % 2 == 0) && (sp->l_count > 0))
			(sp->size < ll) ? (sp->size = ll) : 0;
		else if (sp->l_count > 0)
			(sp->size < l) ? (sp->size = l) : 0;
	}
	if (sp->conversion == D)
		(sp->size < l) ? sp->size = l : 0;
	if (sp->conversion == O)
		(sp->size < l) ? sp->size = l : 0;
	if (sp->conversion == U)
		(sp->size < l) ? sp->size = l : 0;
	if (sp->conversion == C)
		(sp->size < l) ? sp->size = l : 0;
}
