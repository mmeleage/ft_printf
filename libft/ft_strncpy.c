/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:31:25 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 15:06:15 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t		src_len;

	src_len = ft_strlen(src);
	if (len > src_len)
	{
		dst = (char *)ft_memcpy(dst, src, src_len);
		ft_bzero(dst + src_len, len - src_len);
	}
	else
		dst = (char *)ft_memcpy(dst, src, len);
	return (dst);
}
