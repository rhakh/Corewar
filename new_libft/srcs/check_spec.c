/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <rhakh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:56:07 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/28 15:06:33 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			check_precision(t_spec *spec, char **str, va_list *cap)
{
	if (ft_isdigit(*(*str)) == 1)
	{
		spec->precision = ft_atoi((*str));
		while ((*(*str) >= '0') && (*(*str) <= '9'))
			(*str)++;
		return (1);
	}
	if (*(*str) == '*')
	{
		spec->precision = va_arg(*cap, int);
		(*str)++;
		return (1);
	}
	return (-1);
}

int			check_size(t_spec *sp, char **str)
{
	if (*(*str + 0) == 'h')
		sp->h_count++;
	else if (*(*str + 0) == 'l')
		sp->l_count++;
	else if (*(*str + 0) == 'j')
		(sp->size < j) ? (sp->size = j) : 0;
	else if (*(*str + 0) == 'z')
		(sp->size < z) ? (sp->size = z) : 0;
	else
		return (-1);
	(*str)++;
	check_size(sp, str);
	return (1);
}

int			check_conversion(t_spec *spec, char **str)
{
	char	*mask;
	int		i;

	i = 0;
	mask = "sSpdDioOuUxXcCb%";
	while (mask[i] != '\0')
	{
		if (*(*str) == mask[i])
		{
			(*str)++;
			spec->conversion = i + 1;
			return (1);
		}
		i++;
	}
	if ((is_flag(*str) == 0) && (is_size(*str) == 0)
		&& (ft_isdigit(*(*str)) == 0))
	{
		spec->conversion = c;
		spec->alone_char = *(*str);
		(*str)++;
		return (1);
	}
	else
		return (-1);
}

int			check_spec(t_spec *spec, char **str, va_list *cap)
{
	check_flags(spec, str);
	check_min_field(spec, str, cap);
	if (*(*str) == '.' && (*str)++)
	{
		spec->precision = 0;
		check_precision(spec, str, cap);
	}
	check_size(spec, str);
	if (check_conversion(spec, str) == 1)
		return (1);
	else
		check_spec(spec, str, cap);
	return (1);
}
