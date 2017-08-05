#ifndef STRP_H
# define STRP_H

# include <stdlib.h>
# include "libft.h"

typedef struct		s_string
{
    char		*str;
    size_t		len;
    size_t		size;
}					t_string;

t_string	*string_new(size_t size);
void		string_del(t_string **res);
int			string_append(t_string *res, const char *str, size_t len);
int			string_append_c(t_string *res, char c);

#endif
