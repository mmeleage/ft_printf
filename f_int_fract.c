/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_int_fract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:45:08 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:45:09 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

char	*int_part_f(int exp, char *pow, char *int_part, char *bits)
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

char	*get_int_part_f(int exp, char *bits)
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

char	*fill_zeroes(char *short_num, char *long_num)
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

char	*fract_part_f(char *bits, int i, char *fract_part, char *pow)
{
	while (bits[i])
	{
		if (bits[i++] == '1')
			fract_part = add(fill_zeroes(fract_part, pow), pow, 0);
		pow = divide(pow);
	}
	return (fract_part);
}

char	*get_fract_part_f(int exp, char *bits)
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
