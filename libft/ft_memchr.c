/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:40:03 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 13:55:59 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_copy;

	s_copy = (unsigned char *)s;
	while (n--)
	{
		if (*s_copy == (unsigned char)c)
			return ((void *)s_copy);
		s_copy++;
	}
	return (NULL);
}
