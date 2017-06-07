/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_d_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:57:17 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:57:19 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			d_flag_with_min(t_spec *sp, t_strp *num, t_strp *field,
									long long value)
{
	if (sp->flags[plus] == 1)
		put_char_to_strp(field, (value >= 0) ? '+' : '-');
	else if (sp->flags[space] == 1)
		put_char_to_strp(field, (value >= 0) ? ' ' : '-');
	else if (value < 0)
		put_char_to_strp(field, '-');
	put_str_to_strp(field, num->str);
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void			d_flag_wout_min(t_spec *sp, t_strp *num, t_strp *field,
								long long value)
{
	if (sp->precision >= 0)
	{
		while ((int)field->i + (int)num->i + 1 < sp->min_field_w)
			put_char_to_strp(field, ' ');
		if (sp->flags[plus] == 1)
			put_char_to_strp(field, (value < 0) ? '-' : '+');
		else if (sp->flags[space] == 1 || value < 0)
			put_char_to_strp(field, (value < 0) ? '-' : ' ');
		else if ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, ' ');
	}
	else
	{
		if (sp->flags[zero] == 0)
			while ((int)field->i + (int)num->i + 1 < sp->min_field_w)
				put_char_to_strp(field, ' ');
		if (sp->flags[plus] == 1)
			put_char_to_strp(field, (value < 0) ? '-' : '+');
		else if (sp->flags[space] == 1)
			put_char_to_strp(field, (value < 0) ? '-' : ' ');
		else if (value < 0)
			put_char_to_strp(field, '-');
		while ((int)field->i + (int)num->i < sp->min_field_w)
			put_char_to_strp(field, (sp->flags[zero] == 1) ? '0' : ' ');
	}
}

t_strp			*get_d_spec(t_spec *sp, va_list *ap)
{
	t_strp		*field;
	t_strp		*num;
	char		*number;
	long long	value;

	field = NULL;
	pre_processing(sp);
	value = cast_num(sp, ap);
	number = lltoa_base(value, 10);
	if (((num = get_prec_num(sp, number)) == NULL)
		|| ((field = new_strp(50)) == NULL))
		return (NULL);
	if (sp->flags[minus] == 1)
		d_flag_with_min(sp, num, field, value);
	else
	{
		d_flag_wout_min(sp, num, field, value);
		put_str_to_strp(field, num->str);
	}
	del_strp(&num);
	ft_strdel(&number);
	return (field);
}
