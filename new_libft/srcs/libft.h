/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:13:29 by rhakh             #+#    #+#             */
/*   Updated: 2017/03/31 23:33:09 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <wchar.h>
# include <wctype.h>
# include <limits.h>

# define BUFF_SIZE 32
# define ABS(x) ((x)<0 ? -(x) : (x))
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1B[37m"
# define EOC		"\x1b[0m"

typedef enum		e_flags
{
	minus, plus, zero, hash, space
}					t_flags;

typedef enum		e_size_mod
{
	hh = 1, h, l, ll, j, z
}					t_size_mod;

typedef enum		e_conversion_letter
{
	s = 1, S, p, d, D, i, o, O, u, U, x, X, c, C, b, perc
}					t_conversion_letter;

typedef struct s_specifications	t_spec;

struct				s_specifications
{
	int				flags[space + 1];
	int				min_field_w;
	int				precision;
	int				size;
	int				conversion;
	char			alone_char;
	int				h_count;
	int				l_count;
	t_spec			*next;
};

typedef struct		s_strp
{
	char			*str;
	size_t			i;
	size_t			last_size;
}					t_strp;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_t
{
	int				fd;
	char			*line;
	size_t			next_line;
	size_t			i;
	size_t			last_size;
	struct s_t		*next;
}					t_t;

int					ft_printf(const char *format, ...);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *b, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *litt, size_t l);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				*ft_memdup(const void *src, size_t n);
int					ft_factorial(int nb);
int					ft_power(int nb, int power);
int					ft_sqrt(int nb);
void				ft_list_reverse(t_list **begin_list);
t_spec				*new_spec(void);
void				erase_spec(t_spec *sp);
void				del_spec(t_spec *specs);
int					check_spec(t_spec *spec, char **str, va_list *cap);
int					check_conversion(t_spec *spec, char **str);
int					check_size(t_spec *sp, char **str);
int					check_precision(t_spec *spec, char **str, va_list *cap);
int					check_min_field(t_spec *spec, char **str, va_list *cap);
int					check_flags(t_spec *spec, char **str);
int					is_size(char *str);
int					is_flag(char *str);
t_strp				*get_result(char *format, t_spec *specs, va_list *ap,
					t_strp *res);
t_strp				*new_strp(size_t size);
void				del_strp(t_strp **t);
int					put_char_to_strp(t_strp *res, char c);
int					put_strp_to_strp(t_strp *res, t_strp *str);
int					put_str_to_strp(t_strp *res, char *str);
int					realloc_strp(t_strp *t);
t_strp				*get_spec(t_spec *sp, va_list *ap);
t_strp				*get_d_spec(t_spec *sp, va_list *ap);
void				d_flag_wout_min(t_spec *sp, t_strp *num, t_strp *f,
					long long v);
void				d_flag_with_min(t_spec *sp, t_strp *num, t_strp *f,
					long long v);
t_strp				*get_x_spec(t_spec *sp, va_list *ap);
void				x_flag_wout_min(t_spec *sp, t_strp *num, t_strp *f,
					unsigned long long v);
void				x_flag_with_min(t_spec *sp, t_strp *num, t_strp *f,
					unsigned long long v);
t_strp				*get_o_spec(t_spec *sp, va_list *ap);
void				o_flag_wout_min(t_spec *sp, t_strp *num, t_strp *f,
					unsigned long long v);
void				o_flag_with_min(t_spec *sp, t_strp *num, t_strp *f,
					unsigned long long v);
t_strp				*get_u_spec(t_spec *sp, va_list *ap);
void				u_flag_wout_min(t_spec *sp, t_strp *num, t_strp *field);
void				u_flag_with_min(t_spec *sp, t_strp *num, t_strp *field);
t_strp				*get_c_spec(t_spec *sp, va_list *ap);
void				c_flag_wout_min(t_spec *sp, char value, t_strp *field);
void				c_flag_with_min(t_spec *sp, char value, t_strp *field);
t_strp				*get_s_spec(t_spec *sp, va_list *ap);
void				s_flag_wout_min(t_spec *sp, char *value, t_strp *field);
void				s_flag_with_min(t_spec *sp, char *value, t_strp *field);
void				pre_processing(t_spec *sp);
t_strp				*get_prec_num(t_spec *sp, char *number);
unsigned long long	ucast_num(t_spec *sp, va_list *ap);
long long			cast_num(t_spec *sp, va_list *ap);
char				*ulltoa_base(unsigned long long num, int base);
void				ullpaste_in_str(unsigned long long num, int base,
					char *str, int *i);
char				*lltoa_base(long long num, int base);
void				llpaste_in_str(long long num, int base, char *str, int *i);
int					realloc_strp(t_strp *t);
void				str_capitalizer(char *str);
t_strp				*get_p_spec(t_spec *sp, va_list *ap);
void				p_flag_wout_min(t_spec *sp, t_strp *num, t_strp *f);
void				p_flag_with_min(t_spec *sp, t_strp *num, t_strp *f);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t len);
t_strp				*get_ls_spec(t_spec *sp, va_list *ap);
void				ls_flag_wout_min(t_spec *sp, wchar_t *value, t_strp *field);
void				ls_flag_with_min(t_spec *sp, wchar_t *value, t_strp *field);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					check_colour(t_strp *res, char **s);
t_strp				*alone_char(t_spec *spec, t_strp *tmp, t_strp *res);
t_strp				*get_b_spec(t_spec *sp, va_list *ap);
void				b_flag_wout_min(t_spec *sp, t_strp *num, t_strp *field,
					unsigned long long value);
void				b_flag_with_min(t_spec *sp, t_strp *num, t_strp *field,
					unsigned long long value);
int					get_next_line(const int fd, char **line);
long long			ft_atoll(const char *str);
void				ft_swap(int *a, int *b);

#endif
