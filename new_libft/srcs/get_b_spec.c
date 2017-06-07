/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_b_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:46:11 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/27 18:46:14 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					b_flag_with_min(t_spec *sp, t_strp *num, t_strp *field,
										unsigned long long v)
{
	if ((sp->flags[hash] == 1) && (v != 0))
		put_str_to_strp(field, "0b");
	put_str_to_strp(field, num->str);
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void					b_flag_wout_min(t_spec *sp, t_strp *num, t_strp *field,
										unsigned long long v)
{
	if (sp->precision >= 0)
	{
		while ((int)field->i + (int)num->i + 2 < sp->min_field_w)
			put_char_to_strp(field, ' ');
		if ((sp->flags[hash] == 1) && (v != 0))
			put_str_to_strp(field, "0b");
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, ' ');
	}
	else
	{
		if (sp->flags[zero] == 0)
			while ((int)field->i + (int)num->i + 2 < sp->min_field_w)
				put_char_to_strp(field, ' ');
		if ((sp->flags[hash] == 1) && (v != 0))
			put_str_to_strp(field, "0b");
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, (sp->flags[zero] == 1) ? '0' : ' ');
	}
}

t_strp					*get_b_spec(t_spec *sp, va_list *ap)
{
	t_strp				*field;
	t_strp				*num;
	char				*number;
	unsigned long long	value;

	field = NULL;
	pre_processing(sp);
	value = ucast_num(sp, ap);
	number = ulltoa_base(value, 2);
	if (((num = get_prec_num(sp, number)) == NULL)
		|| ((field = new_strp(50)) == NULL))
		return (NULL);
	if (sp->flags[minus] == 1)
		b_flag_with_min(sp, num, field, value);
	else
	{
		b_flag_wout_min(sp, num, field, value);
		put_str_to_strp(field, num->str);
	}
	del_strp(&num);
	ft_strdel(&number);
	return (field);
}
