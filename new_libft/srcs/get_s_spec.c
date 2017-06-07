/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_s_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:57:56 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:57:57 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			s_flag_with_min(t_spec *sp, char *value, t_strp *field)
{
	if (sp->precision > 0)
	{
		while ((*value != '\0') && (sp->precision > 0))
		{
			put_char_to_strp(field, *value);
			value++;
			sp->precision--;
		}
	}
	else
		put_str_to_strp(field, value);
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void			s_flag_wout_min(t_spec *sp, char *value, t_strp *field)
{
	t_strp		*prec_str;

	if ((prec_str = new_strp(50)) == NULL)
		return ;
	if (sp->precision >= 0)
	{
		while ((*value != '\0') && (sp->precision > 0))
		{
			put_char_to_strp(prec_str, *value);
			value++;
			sp->precision--;
		}
	}
	else
		put_str_to_strp(prec_str, value);
	while ((int)field->i + (int)prec_str->i < sp->min_field_w)
		put_char_to_strp(field, (sp->flags[zero] == 1) ? '0' : ' ');
	put_strp_to_strp(field, prec_str);
	del_strp(&prec_str);
}

t_strp			*get_s_spec(t_spec *sp, va_list *ap)
{
	t_strp		*field;
	char		*value;

	field = NULL;
	pre_processing(sp);
	value = va_arg(*ap, char *);
	if (value == NULL)
		value = "(null)";
	if ((field = new_strp(50)) == NULL)
		return (NULL);
	if (sp->flags[minus] == 1)
		s_flag_with_min(sp, value, field);
	else
		s_flag_wout_min(sp, value, field);
	return (field);
}
