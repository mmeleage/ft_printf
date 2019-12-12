/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_multiply_divide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:45:14 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 19:23:54 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_product(int i, int j, char *num, char *res)
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

char	*multiply(char *num)
{
	char	*res;
	int		i;
	int		j;
	int		len;

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

char	*divide(char *num)
{
	char	*res;
	int		i;
	int		j;
	int		mod;
	int		len;

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
