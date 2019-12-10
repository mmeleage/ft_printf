/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:35:30 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/18 17:50:49 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static int		ft_newsize(char const *s)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len;

	len = ft_strlen(s);
	if (len == 0)
		return (0);
	i = 0;
	j = len - 1;
	while (ft_is_space(s[i]))
		i++;
	if (i == j + 1)
		return (-1);
	while (ft_is_space(s[j]))
		j--;
	return (j - i + 1);
}

char			*ft_strtrim(char const *s)
{
	char			*str;
	int				new_size;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	new_size = ft_newsize(s);
	if (new_size == 0)
		return ((char *)s);
	if (new_size == -1)
		return (ft_strnew(0));
	str = (char *)malloc(new_size + 1);
	if (str == NULL)
		return (NULL);
	while (ft_is_space(s[i]))
		i++;
	str = ft_strsub(s, i, new_size);
	if (str == NULL)
		return (NULL);
	str[new_size] = '\0';
	return (str);
}
