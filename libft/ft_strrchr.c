/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:50:56 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 18:41:46 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	while (*s)
	{
		if (ft_strchr(s, c) && \
				!ft_strchr(ft_strdup(s + 1), c))
			return ((char *)s);
		s++;
	}
	if (ft_strchr(s, c))
		return ((char *)s);
	return (NULL);
}
