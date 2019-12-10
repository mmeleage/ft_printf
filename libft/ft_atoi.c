/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:00:24 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 18:17:52 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checklimits(long long num, int sign, const char *str)
{
	if (num * sign > 922337203685477580 && *(str + 1) >= '0' && *(str + 1)\
			<= '9')
		return (-1);
	if (num == 922337203685477580 && *(str + 1) <= '9')
	{
		if (sign == 1 && *(str + 1) > '7')
			return (-1);
		else if (sign == -1 && *(str + 1) > '8')
			return (0);
	}
	if (num * sign < -922337203685477580 && *(str + 1) >= '0' && *(str +\
				1) <= '9')
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	int			sign;
	long long	num;
	int			check_limits;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == \
			'\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = 10 * num + *str - '0';
		check_limits = ft_checklimits(num, sign, str);
		if (check_limits != 1)
			return (check_limits);
		str++;
	}
	return (num * sign);
}
