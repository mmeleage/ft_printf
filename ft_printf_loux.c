/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_loux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:46:14 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:46:15 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

int		count_digits_lu(unsigned long int n, int base)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= base;
	}
	return (len);
}

char	*ft_itoa_lu(unsigned long int n, int base, char x)
{
	char	*str;
	int		i;
	int		len;

	len = count_digits_lu(n, base);
	i = len - 1;
	str = (char *)malloc(i + 2);
	if (n == 0)
		str[0] = '0';
	str[i + 1] = '\0';
	while (n)
	{
		if (n % base < 10)
			str[i] = n % base + '0';
		else if (x == 'x')
			str[i] = 'a' + n % base - 10;
		else
			str[i] = 'A' + n % base - 10;
		i--;
		n /= base;
	}
	return (str);
}
