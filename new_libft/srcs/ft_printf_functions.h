#ifndef FT_PRINTF_FUNCTIONS_H
# define FT_PRINTF_FUNCTIONS_H

# include "libft.h"

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

#endif
