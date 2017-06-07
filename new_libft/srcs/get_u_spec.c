/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_u_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:58:18 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:58:21 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					u_flag_with_min(t_spec *sp, t_strp *num, t_strp *field)
{
	put_str_to_strp(field, num->str);
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void					u_flag_wout_min(t_spec *sp, t_strp *num, t_strp *field)
{
	if (sp->precision >= 0)
	{
		while ((int)field->i + (int)num->i + 1 < sp->min_field_w)
			put_char_to_strp(field, ' ');
		if ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, ' ');
	}
	else
	{
		if (sp->flags[zero] == 0)
			while ((int)field->i + (int)num->i + 1 < sp->min_field_w)
				put_char_to_strp(field, ' ');
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, (sp->flags[zero] == 1) ? '0' : ' ');
	}
}

t_strp					*get_u_spec(t_spec *sp, va_list *ap)
{
	t_strp				*field;
	t_strp				*num;
	char				*number;
	unsigned long long	value;

	field = NULL;
	pre_processing(sp);
	value = ucast_num(sp, ap);
	number = ulltoa_base(value, 10);
	if (((num = get_prec_num(sp, number)) == NULL)
		|| ((field = new_strp(50)) == NULL))
		return (NULL);
	if (sp->flags[minus] == 1)
		u_flag_with_min(sp, num, field);
	else
	{
		u_flag_wout_min(sp, num, field);
		put_str_to_strp(field, num->str);
	}
	del_strp(&num);
	ft_strdel(&number);
	return (field);
}
