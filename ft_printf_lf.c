/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:46:01 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:46:01 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

char	*get_bits_lf(long double num)
{
	char            *bits;
	unsigned char   *num_addr;
	int             i;

	i = 0;
	num_addr = (unsigned char *)&num;
	bits = (char *)malloc(81);
	while (i < 80)
	{
		bits[80 - i - 1] = ((*num_addr) & 1) + '0';
		(*num_addr) >>= 1;
		if ((i + 1) % 8 == 0)
			num_addr++;
		i++;
	}
	bits[81] = '\0';
	return (bits);
}

int		get_exponent_lf(char *bits)
{
	int     i;
	int     exp;
	int     pow;

	exp = 0;
	i = 15;
	pow = 1;
	while (i)
	{
		exp += (bits[i] - '0') * pow;
		pow *= 2;
		i--;
	}
	return (exp - 16383);
}

char	*get_int_part_lf(int exp, char *bits)
{
	char    *int_part;
	int     i;
	int     j;
	char    *pow;

	i = 0;
	j = 16;
	pow = ft_strdup("1");
	int_part = ft_strdup("0");
	if (exp > 0)
	{
		while (exp >= 0 && bits[j])
		{
			i = 0;
			pow = ft_strcpy(pow, "1");
			while (i++ < exp)
				pow = multiply(pow);
			if (bits[j++] == '1')
				int_part = add(int_part, pow, 1);
			exp--;
		}
	}
	else if (exp == 0)
		int_part = ft_strcpy(int_part, "1");
	return (int_part);
}

char	*get_fract_part_lf(int exp, char *bits)
{
	char    *fract_part;
	char    *pow;
	int     i;

	pow = ft_strdup("5");
	fract_part = ft_strdup("0");
	if (exp < 63)
	{
		if (exp < 0)
		{
			i = -exp - 1;
			while (i--)
				pow = divide(pow);
			fract_part = add(fill_zeroes(fract_part, pow), pow, 0);
			pow = divide(pow);
		}
		i = (exp < 0) ? 17 : (17 + exp);
		fract_part = fract_part_f(bits, i, fract_part, pow);
	}
	return (fract_part);
}
