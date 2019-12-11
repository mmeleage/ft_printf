/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:38:37 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/18 17:41:05 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == \
					'\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_wordlen(char const *s, int index, char c)
{
	int		count;
	int		i;

	count = 0;
	i = index;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

static char	**ft_free(char **arr, int size)
{
	int		i;

	i = 0;
	while (size--)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static char	**ft_newarr(char *s, char c)
{
	if (s == NULL)
		return (NULL);
	return ((char **)malloc((ft_countwords(s, c) + 1) * \
	sizeof(char *)));
}

char		**ft_strsplit(char const *s, char c)
{
	char	**words_arr;
	int		i;
	int		j;

	if ((words_arr = ft_newarr((char *)s, c)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if ((words_arr[j++] = ft_strsub(s, i, ft_wordlen(s, i, c))) == NULL)
				return (ft_free(words_arr, j - 1));
			i += ft_wordlen(s, i, c);
		}
		else
			i++;
	}
	words_arr[j] = NULL;
	return (words_arr);
}
