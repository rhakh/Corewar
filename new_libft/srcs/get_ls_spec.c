/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ls_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 22:03:51 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/24 22:03:57 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ls_flag_with_min(t_spec *sp, wchar_t *value, t_strp *field)
{
	if (sp->precision > 0)
	{
		while ((*value != '\0') && (sp->precision > 0))
		{
			put_char_to_strp(field, (char)*value);
			value++;
			sp->precision--;
		}
	}
	else
	{
		while (*value != '\0')
		{
			put_char_to_strp(field, (char)*value);
			value++;
		}
	}
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void			ls_flag_wout_min(t_spec *sp, wchar_t *value, t_strp *field)
{
	t_strp		*prec_str;

	if ((prec_str = new_strp(50)) == NULL)
		return ;
	if (sp->precision >= 0)
	{
		while ((*value != '\0') && (sp->precision > 0))
		{
			put_char_to_strp(prec_str, (char)*value);
			value++;
			sp->precision--;
		}
	}
	else
	{
		while (*value != '\0')
		{
			put_char_to_strp(prec_str, (char)*value);
			value++;
		}
	}
	while ((int)field->i + (int)prec_str->i < sp->min_field_w)
		put_char_to_strp(field, (sp->flags[zero] == 1) ? '0' : ' ');
	put_strp_to_strp(field, prec_str);
	del_strp(&prec_str);
}

t_strp			*get_ls_spec(t_spec *sp, va_list *ap)
{
	t_strp		*field;
	wchar_t		*value;

	field = NULL;
	pre_processing(sp);
	value = va_arg(*ap, wchar_t *);
	if (value == NULL)
		value = L"(null)";
	if ((field = new_strp(50)) == NULL)
		return (NULL);
	if (sp->flags[minus] == 1)
		ls_flag_with_min(sp, value, field);
	else
		ls_flag_wout_min(sp, value, field);
	return (field);
}
