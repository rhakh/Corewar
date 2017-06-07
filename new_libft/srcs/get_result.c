/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_result.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:57:43 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:57:45 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_strp			*alone_char(t_spec *spec, t_strp *tmp, t_strp *res)
{
	erase_spec(spec);
	del_strp(&tmp);
	res->i = ft_strlen(res->str);
	return (res);
}

t_strp			*get_result(char *format, t_spec *spec, va_list *ap,
							t_strp *res)
{
	t_strp		*tmp;

	while (*format != '\0')
	{
		if ((*format == '{') && (*format != '\0'))
			check_colour(res, &format);
		if ((*format == '%') && (*format != '\0'))
		{
			format++;
			check_spec(spec, &format, ap);
			tmp = get_spec(spec, ap);
			put_strp_to_strp(res, tmp);
			if (spec->alone_char == 0)
				return (alone_char(spec, tmp, res));
			erase_spec(spec);
			del_strp(&tmp);
		}
		else if ((check_colour(res, &format) == 0) && (*format != '\0'))
		{
			put_char_to_strp(res, *format);
			format++;
		}
	}
	return (res);
}
