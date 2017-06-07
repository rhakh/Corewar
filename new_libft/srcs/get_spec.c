/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:58:05 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:58:07 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_strp			*get_spec(t_spec *sp, va_list *ap)
{
	if ((sp->conversion == d) || (sp->conversion == D)
		|| (sp->conversion == i))
		return (get_d_spec(sp, ap));
	else if ((sp->conversion == x) || (sp->conversion == X))
		return (get_x_spec(sp, ap));
	else if ((sp->conversion == o) || (sp->conversion == O))
		return (get_o_spec(sp, ap));
	else if ((sp->conversion == u) || (sp->conversion == U))
		return (get_u_spec(sp, ap));
	else if ((sp->conversion == c) || (sp->conversion == C))
		return (get_c_spec(sp, ap));
	else if (sp->conversion == s)
		return (get_s_spec(sp, ap));
	else if (sp->conversion == perc && (sp->alone_char = '%'))
		return (get_c_spec(sp, ap));
	else if (sp->conversion == p && (sp->flags[hash] = 1))
		return (get_p_spec(sp, ap));
	else if (sp->conversion == S)
		return (get_ls_spec(sp, ap));
	else if (sp->conversion == b)
		return (get_b_spec(sp, ap));
	return (NULL);
}
