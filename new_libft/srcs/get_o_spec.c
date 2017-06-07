/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_o_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:57:27 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:57:29 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					o_flag_with_min(t_spec *sp, t_strp *num, t_strp *field,
										unsigned long long value)
{
	if ((sp->flags[hash] == 1) && (value != 0) && (num->str[0] != '0'))
		put_str_to_strp(field, "0");
	put_str_to_strp(field, num->str);
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void					o_flag_wout_min(t_spec *sp, t_strp *num, t_strp *field,
										unsigned long long value)
{
	if (sp->precision >= 0)
	{
		while ((int)field->i + (int)num->i + 1 < sp->min_field_w)
			put_char_to_strp(field, ' ');
		if ((sp->flags[hash] == 1) && (num->str[0] != '0'))
			put_str_to_strp(field, "0");
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, ' ');
	}
	else
	{
		if (sp->flags[zero] == 0)
			while ((int)field->i + (int)num->i + 1 < sp->min_field_w)
				put_char_to_strp(field, ' ');
		if ((sp->flags[hash] == 1) && (value != 0))
			put_str_to_strp(field, "0");
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, (sp->flags[zero] == 1) ? '0' : ' ');
	}
}

t_strp					*get_o_spec(t_spec *sp, va_list *ap)
{
	t_strp				*field;
	t_strp				*num;
	char				*number;
	unsigned long long	value;

	field = NULL;
	pre_processing(sp);
	value = ucast_num(sp, ap);
	number = ulltoa_base(value, 8);
	if (((num = get_prec_num(sp, number)) == NULL)
		|| ((field = new_strp(50)) == NULL))
		return (NULL);
	if (sp->flags[minus] == 1)
		o_flag_with_min(sp, num, field, value);
	else
	{
		o_flag_wout_min(sp, num, field, value);
		put_str_to_strp(field, num->str);
	}
	del_strp(&num);
	ft_strdel(&number);
	return (field);
}
