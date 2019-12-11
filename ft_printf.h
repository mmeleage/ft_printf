# ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

# include <stdio.h>
# include <float.h>
# pragma GCC diagnostic ignored "-Wformat"

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
char            *get_int_part_f(int exp, char *bits);
char            *fill_zeroes(char *short_num, char *long_num);
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
t_flag          fill_sizes(char *format, int *j, t_flag flags);
void            fill_num_funcs(t_func *funcs, t_flag flags, va_list arg);
void            fill_oxnum_funcs(t_func *funcs, t_flag flags, va_list arg);
char            *get_num(t_flag flags, t_func funcs);
char            *get_arg(t_flag flags, va_list arg);
int             count_spaces_to_width(t_flag flags, int len, char *s);
int             print_arg_with_flags(t_flag flags, va_list arg);
int             ft_printf(const char *restrict format, ...);

# endif