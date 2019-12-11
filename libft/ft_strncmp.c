/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:53:29 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/15 15:33:10 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		len1;
	size_t		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 < n || len2 < n)
		return (ft_memcmp(s1, s2, len1 > len2 ? len1 : len2));
	else
		return (ft_memcmp(s1, s2, n));
}
