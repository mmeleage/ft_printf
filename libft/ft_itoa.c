/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:28:33 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 17:50:12 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		nbr_len;

	nbr_len = ft_nbrlen(n);
	i = n < 0 ? nbr_len : nbr_len - 1;
	str = (char *)malloc(i + 2);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[i + 1] = '\0';
	if (n < 0)
		str[0] = '-';
	while (n)
	{
		str[i--] = n < 0 ? -(n % 10) + '0' : n % 10 + '0';
		n /= 10;
	}
	return (str);
}
