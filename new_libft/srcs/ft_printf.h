/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:36:26 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 16:36:27 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <wchar.h>
# include <wctype.h>
# include <limits.h>

int					ft_printf(const char *format, ...);
int					ft_snprintf(char *str, size_t n, const char *format, ...);

#endif
