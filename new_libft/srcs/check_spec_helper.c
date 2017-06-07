/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spec_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:56:24 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:56:27 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_flag(char *str)
{
	if (str[0] == '-')
		return (1);
	if (str[0] == '+')
		return (1);
	if (str[0] == '0')
		return (1);
	if (str[0] == ' ')
		return (1);
	if (str[0] == '#')
		return (1);
	if (str[0] == '\'')
		return (1);
	if (str[0] == '*')
		return (1);
	if (str[0] == 'L')
		return (1);
	if (str[0] == '$')
		return (1);
	if (str[0] == '.')
		return (1);
	return (0);
}

int		is_size(char *str)
{
	if (str[0] == 'l' && str[1] == 'l')
		return (1);
	if (str[0] == 'l')
		return (1);
	if (str[0] == 'h' && str[1] == 'h')
		return (1);
	if (str[0] == 'h')
		return (1);
	if (str[0] == 'j')
		return (1);
	if (str[0] == 'z')
		return (1);
	if (str[0] == 'L')
		return (1);
	return (0);
}

int		check_flags(t_spec *spec, char **str)
{
	if (*(*str) == ' ')
		spec->flags[space] = 1;
	else if (*(*str) == '0')
		spec->flags[zero] = 1;
	else if (*(*str) == '-')
		spec->flags[minus] = 1;
	else if (*(*str) == '+')
		spec->flags[plus] = 1;
	else if (*(*str) == '#')
		spec->flags[hash] = 1;
	else
		return (-1);
	(*str)++;
	check_flags(spec, str);
	return (1);
}

int		check_min_field(t_spec *spec, char **str, va_list *cap)
{
	if (ft_isdigit(*(*str)) == 1)
	{
		spec->min_field_w = ft_atoi((*str));
		while ((*(*str) >= '0') && (*(*str) <= '9'))
			(*str)++;
		return (1);
	}
	if (*(*str) == '*')
	{
		spec->min_field_w = va_arg(*cap, int);
		if (spec->min_field_w < 0 && (spec->flags[minus] = 1))
			spec->min_field_w *= -1;
		(*str)++;
		return (1);
	}
	return (-1);
}
