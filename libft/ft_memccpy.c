/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:07:15 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 18:20:02 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;
	size_t			i;

	dst_copy = (unsigned char *)dst;
	src_copy = (unsigned char *)src;
	if (dst_copy == NULL && src_copy == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst_copy[i] = src_copy[i];
		if (src_copy[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
