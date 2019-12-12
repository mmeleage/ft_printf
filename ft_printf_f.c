/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:34:38 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:24:40 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

char	*get_bits_f(double num)
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

int		get_exponent_f(char *bits)
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

char	*round_digits(char *num, int i, int *flag)
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

char	*complete_with_zeroes(int precision, char *fract_part, int i)
{
	char    *new_fract_part;
	
	new_fract_part = (char *)malloc(precision + 1);
	new_fract_part = ft_strcpy(new_fract_part, fract_part);
	while (precision - i)
		new_fract_part[i++] = '0';
	new_fract_part[i] = '\0';
	return (new_fract_part);
}

char	*round_num(char *int_part, char *fract_part, int precision)
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
