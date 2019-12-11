/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:15:27 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 15:13:31 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	needle_len;
	size_t	haystack_len;

	needle_len = ft_strlen(needle);
	haystack_len = ft_strlen(haystack);
	if (needle_len == 0)
		return ((char *)haystack);
	if (haystack_len < needle_len)
		return (NULL);
	while (*haystack)
	{
		if (ft_memcmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
