/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:22:17 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 18:26:09 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (n < size2)
	{
		ft_memcpy(s1 + size1, s2, n);
		s1[size1 + n] = '\0';
	}
	else
	{
		ft_memcpy(s1 + size1, s2, size2);
		s1[size1 + size2] = '\0';
	}
	return (s1);
}
