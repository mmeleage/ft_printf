/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:46:36 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:46:36 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

//# pragma GCC diagnostic ignored "-Wformat"

typedef struct  s_flag
{
	int         minus;
	int         plus;
	int         zero;
	int         space;
	int         sharp;
	int         width;
	int         precision;
	int         h;
	int         l;
	int         lf;
	char        conversion;
}               t_flag;

typedef struct  s_func
{
	char        *hhs;
	char        *hs;
	char        *lls;
	char        *ls;
	char        *s;
}               t_func;

char            *ft_ptoa(void *p);

int             count_digits_hh(char n);
char		    *ft_itoa_hh(char n);

int             count_digits_h(short int n);
char		    *ft_itoa_h(short int n);

int             count_digits_ll(long long int n);
char		    *ft_itoa_ll(long long int n);

int             count_digits_l(long int n);
char		    *ft_itoa_l(long int n);

int             count_digits_u(unsigned int n, int base);
char		    *ft_itoa_u(unsigned int n, int base, char x);

int             count_digits_hhu(unsigned char n, int base);
char		    *ft_itoa_hhu(unsigned char n, int base, char x);

int             count_digits_hu(unsigned short int n, int base);
char		    *ft_itoa_hu(unsigned short int n, int base, char x);

int             count_digits_llu(unsigned long long int n, int base);
char		    *ft_itoa_llu(unsigned long long int n, int base, char x);

int             count_digits_lu(unsigned long int n, int base);
char		    *ft_itoa_lu(unsigned long int n, int base, char x);

char            *get_bits_f(double num);
int             get_exponent_f(char *bits);
void            get_digits(char *res1, char *res2, char num1, char num2);
char            *get_sum(char *num1, char *num2, char *res, int k);
char            *add(char *num1, char *num2, int flag);
char            *get_product(int i, int j, char *num, char *res);
char            *multiply(char *num);
char            *divide(char *num);
char            *int_part_f(int exp, char *pow, char *int_part, char *bits);
char            *get_int_part_f(int exp, char *bits);
char            *fill_zeroes(char *short_num, char *long_num);
char            *fract_part_f(char *bits, int i, char *fract_part, char *pow);
char            *get_fract_part_f(int exp, char *bits);
char            *round_digits(char *num, int i, int *flag);
char            *complete_with_zeroes(int precision, char *fract_part, int i);
char            *round_num(char *int_part, char *fract_part, int precision);

char            *get_bits_lf(long double num);
int             get_exponent_lf(char *bits);
char            *get_int_part_lf(int exp, char *bits);
char            *get_fract_part_lf(int exp, char *bits);

int             is_conversion(char c);
int             is_flag(char c);
int             is_size(char c);
void            initialize_flags(t_flag *flags);
t_flag          fill_flags(char c, int *j, t_flag flags);
t_flag          fill_sizes_h(char *format, int *j, t_flag flags);
t_flag          fill_sizes_l(char *format, int *j, t_flag flags);
void            fill_num_funcs_d(t_func *funcs, t_flag flags, va_list arg);
void            fill_num_funcs_u(t_func *funcs, t_flag flags, va_list arg);
void            fill_num_funcs_o(t_func *funcs, t_flag flags, va_list arg);
void            fill_num_funcs_x(t_func *funcs, t_flag flags, va_list arg);
char            *get_num(t_flag flags, t_func funcs);
char            *get_c(va_list arg);
char            *get_s(t_flag flags, va_list arg);
char            *get_f(t_flag flags, va_list arg);
char            *get_lf(t_flag flags, va_list arg);
char            *get_arg(t_flag flags, va_list arg);
int             spaces_to_width_sharp(t_flag flags, char *s, int spaces_to_width);
int             count_spaces_to_width(t_flag flags, int len, char *s);
void			print_spaces_left(t_flag flags, int spaces_to_width);
void			print_plus_space(t_flag flags, char **s, int *count, int *len);
void			print_p_sharp(t_flag flags, int *count, int len, char *s);
void			print_zero_precision(t_flag flags, int len, int *count);
void			print_arg(t_flag flags, char *s, int *count, int len);
void			print_spaces_right(t_flag flags, int spaces_to_width);
int             print_arg_with_flags(t_flag flags, va_list arg);
t_flag			ft_printf_precision(t_flag flags, va_list arg, char *format, int *j);
t_flag			ft_printf_width(t_flag flags, va_list arg, int *j);
t_flag			ft_printf_flags(char *format, int *j, t_flag flags, va_list arg);
int				ft_printf_count(char *format, t_flag flags, va_list arg, int count);
int             ft_printf(const char *restrict format, ...);

# endif
