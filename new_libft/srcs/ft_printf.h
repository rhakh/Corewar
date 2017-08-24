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
int					ft_snprintf(char **str, size_t n, const char *format, ...);

#endif
