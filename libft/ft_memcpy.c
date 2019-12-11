/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:50:09 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 13:51:43 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;

	dst_copy = (unsigned char *)dst;
	src_copy = (unsigned char *)src;
	if (dst_copy == NULL && src_copy == NULL)
		return (NULL);
	while (n--)
		*dst_copy++ = *src_copy++;
	return (dst);
}
