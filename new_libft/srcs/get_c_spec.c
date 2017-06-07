/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_c_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:57:09 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:57:11 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		c_flag_with_min(t_spec *sp, char value, t_strp *field)
{
	put_char_to_strp(field, value);
	while ((int)field->i < sp->min_field_w)
		put_char_to_strp(field, ' ');
}

void		c_flag_wout_min(t_spec *sp, char value, t_strp *field)
{
	while ((int)field->i + 1 < sp->min_field_w)
		put_char_to_strp(field, (sp->flags[zero]) == 1 ? '0' : ' ');
	put_char_to_strp(field, value);
}

t_strp		*get_c_spec(t_spec *sp, va_list *ap)
{
	t_strp	*field;
	char	value;

	field = NULL;
	pre_processing(sp);
	if (sp->alone_char == -1)
		value = (char)va_arg(*ap, int);
	else
		value = sp->alone_char;
	if ((field = new_strp(50)) == NULL)
		return (NULL);
	if (sp->alone_char == 0)
	{
		put_char_to_strp(field, '\0');
		return (field);
	}
	if (sp->flags[minus] == 1)
		c_flag_with_min(sp, value, field);
	else
		c_flag_wout_min(sp, value, field);
	return (field);
}
