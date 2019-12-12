/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:34:38 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 13:56:10 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

char    *get_bits_f(double num)
{
    char            *bits;
    unsigned char   *num_addr;
    int             i;

    i = 0;
    num_addr = (unsigned char *)&num;
    bits = (char *)malloc(65);
    while (i < 64)
    {
        bits[64 - i - 1] = ((*num_addr) & 1) + '0';
        (*num_addr) >>= 1;
        if ((i + 1) % 8 == 0)
            num_addr++;
        i++;
    }
    bits[65] = '\0';
    return (bits);
}

int     get_exponent_f(char *bits)
{
    int     i;
    int     exp;
    int     pow;

    exp = 0;
    i = 11;
    pow = 1;
    while (i)
    {
        exp += (bits[i] - '0') * pow;
        pow *= 2;
        i--;
    }
    return (exp - 1023);
}

void    get_digits(char *res1, char *res2, char num1, char num2)
{
    if ((*res1 - '0' + num1 - '0' + num2 - '0') > 9)
    {
        *res1 = (*res1 - '0' + num1 - '0' + num2 - '0') % 10 + '0';
        *res2 = *res2 + 1;
    }
    else
        *res1 = *res1 + num1 - '0' + num2 - '0';
}

char    *get_sum(char *num1, char *num2, char *res, int k)
{
    int     i;
    int     j;

    i = ft_strlen(num1) - 1;
    j = ft_strlen(num2) - 1;
    while (i >= 0 || j >= 0)
    {
        if (i < 0)
            get_digits(&res[k], &res[k - 1], '0', num2[j]);
        else if (j < 0)
            get_digits(&res[k], &res[k - 1], num1[i], '0');
        else
            get_digits(&res[k], &res[k - 1], num1[i], num2[j]);
        i--;
        j--;
        k--;
    }
    return (res);
}

char    *add(char *num1, char *num2, int flag)
{
    int     k;
    int     len;
    int     len1;
    int     len2;
    char    *res;

    len1 = ft_strlen(num1);
    len2 = ft_strlen(num2);
    len = (len1 > len2) ? len1 : len2;
    res = (char *)malloc(len + 1 + 1);
    k = 0;
    while (k < len + 1)
        res[k++] = '0';
    res[k] = '\0';
    k = len;
    res = get_sum(num1, num2, res, k);
    if (flag)
        while (*res == '0')
            res++;
    else
        res++;
    return (res);
}

char    *get_product(int i, int j, char *num, char *res)
{
    while (i >= 0)
    {
        if ((res[j] - '0' + (num[i] - '0') * 2) > 9)
        {
            res[j] = res[j] + ((num[i] - '0') * 2) % 10;
            res[j - 1] = res[j - 1] + ((num[i] - '0') * 2) / 10;
        }
        else
            res[j] = res[j] + (num[i] - '0') * 2;
        i--;
        j--;
    }
    return (res);
}

char    *multiply(char *num)
{
    char    *res;
    int     i;
    int     j;
    int     len;

    len = ft_strlen(num);
    res = (char *)malloc(len + 1 + 1);
    j = 0;
    while (j < len + 1)
        res[j++] = '0';
    i = len - 1;
    j = len;
    res = get_product(i, j, num, res);
    res[len + 1] = '\0';
    while (*res == '0')
        res++;
    return (res);
}

char    *divide(char *num)
{
    char    *res;
    int     i;
    int     j;
    int     mod;
    int     len;

    len = ft_strlen(num);
    res = (char *)malloc(len + 1 + 1);
    i = 0;
    j = 0;
    mod = 0;
    while (num[i])
    {
        res[j] = (mod * 10 + num[i] - '0') / 2 + '0';
        mod = (mod * 10 + num[i] - '0') % 2;
        i++;
        j++;
    }
    res[len] = '5';
    res[len + 1] = '\0';
    return (res);
}

char    *int_part_f(int exp, char *pow, char *int_part, char *bits)
{
    int     i;
    int     j;

    i = 0;
    j = 12;
    while (i++ < exp)
        pow = multiply(pow);
    int_part = add(int_part, pow, 1);
    while (exp && bits[j])
    {
        i = 0;
        pow = ft_strcpy(pow, "1");
        while (i++ < exp - 1)
            pow = multiply(pow);
        if (bits[j++] == '1')
            int_part = add(int_part, pow, 1);
        exp--;
    }
    return (int_part);
}

char    *get_int_part_f(int exp, char *bits)
{
    char    *int_part;
    char    *pow;

    pow = ft_strdup("1");
    int_part = ft_strdup("0");
    if (exp > 0)
        int_part = int_part_f(exp, pow, int_part, bits);
    else if (exp == 0)
        int_part = ft_strcpy(int_part, "1");
    return (int_part);
}

char    *fill_zeroes(char *short_num, char *long_num)
{
    int     len1;
    int     len2;
    char    *long_short;
    int     i;
    int     j;

    len1 = ft_strlen(short_num);
    len2 = ft_strlen(long_num);
    i = 0;
    j = 0;
    long_short = (char *)malloc(len2 + 1);
    while (short_num[i])
    {        
        long_short[i] = short_num[i];
        i++;
    }
    while (long_num[i])
        long_short[i++] = '0';
    long_short[len2] = '\0';
    return (long_short);
}

char    *fract_part_f(char *bits, int i, char *fract_part, char *pow)
{
    while (bits[i])
    {
        if (bits[i++] == '1')
            fract_part = add(fill_zeroes(fract_part, pow), pow, 0);
        pow = divide(pow);
    }
    return (fract_part);
}

char    *get_fract_part_f(int exp, char *bits)
{
    char    *fract_part;
    char    *pow;
    int     i;

    pow = ft_strdup("5");
    fract_part = ft_strdup("0");
    if (exp < 52)
    {
        if (exp < 0)
        {
            while (exp++ < -1)
                pow = divide(pow);
            fract_part = add(fill_zeroes(fract_part, pow), pow, 0);
            pow = divide(pow);
            i = 12;
        }
        else
            i = 12 + exp;
        fract_part = fract_part_f(bits, i, fract_part, pow);
    }
    return (fract_part);
}

char    *round_digits(char *num, int i, int *flag)
{
    while (i >= 0)
    {
        if (num[i] - '0' + 1 > 9)
        {
            num[i] = (num[i] - '0' + 1) % 10 + '0';
            *flag = 1;
        }
        else
        {
            num[i] = num[i] + 1;
            *flag = 0;
            break;
        }
        i--;
    }
    return (num);
}

char    *complete_with_zeroes(int precision, char *fract_part, int i)
{
    char    *new_fract_part;
    
    new_fract_part = (char *)malloc(precision + 1);
    new_fract_part = ft_strcpy(new_fract_part, fract_part);
    while (precision - i)
        new_fract_part[i++] = '0';
    new_fract_part[i] = '\0';
    return (new_fract_part);
}

char    *round_num(char *int_part, char *fract_part, int precision)
{
    int     i;
    int     flag;
    char    *new_fract_part;

    i = ft_strlen(fract_part);
    if (precision >= i)
    {
        new_fract_part = complete_with_zeroes(precision, fract_part, i);
        return (ft_strjoin(int_part, ft_strjoin(".", new_fract_part)));
    }
    if (fract_part[precision] >= '5')
    {
        i = precision - 1;
        fract_part = round_digits(fract_part, i, &flag);
        if (flag)
        {
            i = ft_strlen(int_part) - 1;
            int_part = round_digits(int_part, i, &flag);
            if (flag)
                int_part = ft_strjoin("1", int_part);
        }
    }
    if (precision == 0)
        return (int_part);
    return (ft_strjoin(int_part, ft_strjoin(".", ft_strsub(fract_part, 0, precision))));
}