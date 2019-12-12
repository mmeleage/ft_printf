/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:44:59 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 19:24:31 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_digits(char *res1, char *res2, char num1, char num2)
{
	if ((*res1 - '0' + num1 - '0' + num2 - '0') > 9)
	{
		*res1 = (*res1 - '0' + num1 - '0' + num2 - '0') % 10 + '0';
		*res2 = *res2 + 1;
	}
	else
		*res1 = *res1 + num1 - '0' + num2 - '0';
}

char	*get_sum(char *num1, char *num2, char *res, int k)
{
	int		i;
	int		j;

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

char	*add(char *num1, char *num2, int flag)
{
	int		k;
	int		len;
	int		len1;
	int		len2;
	char	*res;

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
