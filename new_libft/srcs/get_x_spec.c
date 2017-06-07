/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:58:29 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:58:31 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					x_flag_with_min(t_spec *sp, t_strp *num, t_strp *field,
										unsigned long long v)
{
	if ((sp->flags[hash] == 1) && (v != 0))
		put_str_to_strp(field, "0x");
	put_str_to_strp(field, num->str);
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void					x_flag_wout_min(t_spec *sp, t_strp *num, t_strp *field,
										unsigned long long v)
{
	if (sp->precision >= 0)
	{
		while ((int)field->i + (int)num->i + 2 < sp->min_field_w)
			put_char_to_strp(field, ' ');
		if ((sp->flags[hash] == 1) && (v != 0))
			put_str_to_strp(field, "0x");
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, ' ');
	}
	else
	{
		if (sp->flags[zero] == 0)
			while ((int)field->i + (int)num->i + 2 < sp->min_field_w)
				put_char_to_strp(field, ' ');
		if ((sp->flags[hash] == 1) && (v != 0))
			put_str_to_strp(field, "0x");
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, (sp->flags[zero] == 1) ? '0' : ' ');
	}
}

t_strp					*get_x_spec(t_spec *sp, va_list *ap)
{
	t_strp				*field;
	t_strp				*num;
	char				*number;
	unsigned long long	value;

	field = NULL;
	pre_processing(sp);
	value = ucast_num(sp, ap);
	number = ulltoa_base(value, 16);
	if (((num = get_prec_num(sp, number)) == NULL)
		|| ((field = new_strp(50)) == NULL))
		return (NULL);
	if (sp->flags[minus] == 1)
		x_flag_with_min(sp, num, field, value);
	else
	{
		x_flag_wout_min(sp, num, field, value);
		put_str_to_strp(field, num->str);
	}
	(sp->conversion == X) ? str_capitalizer(field->str) : 0;
	del_strp(&num);
	ft_strdel(&number);
	return (field);
}
