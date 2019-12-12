/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_to_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:47:00 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 19:38:58 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

int		spaces_to_width_sharp(t_flag flags, char *s, int spaces_to_width)
{
	if (flags.sharp)
	{
		if ((s[0] != '0' && ft_strchr("oO", flags.conversion)) ||\
		ft_strchr("fF", flags.conversion))
			spaces_to_width--;
		if (s[0] != '0' && ft_strchr("xX", flags.conversion))
			spaces_to_width -= 2;
	}
	return (spaces_to_width);
}

int		count_spaces_to_width(t_flag flags, int len, char *s)
{
	int		spaces_to_width;

	spaces_to_width = 0;
	if (flags.width > len)
	{
		spaces_to_width = flags.width;
		if ((s[0] == '0' && !(ft_strchr("dDioOuUxX", flags.conversion) &&\
		!flags.precision)) || s[0] != '0')
			spaces_to_width -= len;
		if (s[0] != '-' && (flags.plus || (flags.space && !flags.plus)))
			spaces_to_width--;
		spaces_to_width = spaces_to_width_sharp(flags, s, spaces_to_width);
		if (flags.conversion == 'p')
			spaces_to_width -= 2;
		if (flags.zero && flags.precision < 0 && !flags.minus)
			spaces_to_width = 0;
		else if (flags.precision != -1 && ft_strchr("dDipoOuUxX", flags.conversion))
		{
			if (s[0] == '-' && flags.precision > len - 1)
				spaces_to_width -= flags.precision - (len - 1);
			if (s[0] != '-' && flags.precision > len)
				spaces_to_width -= flags.precision - len;
		}
	}
	return (spaces_to_width);
}

void	print_spaces_left(t_flag flags, int spaces_to_width)
{
	int		i;

	if (!flags.minus)
	{
		i = spaces_to_width;
		while (i-- > 0)
			ft_putchar(' ');
	}
}

void	print_spaces_right(t_flag flags, int spaces_to_width)
{
	int		i;

	if (flags.minus)
	{
		i = spaces_to_width;
		while (i-- > 0)
			ft_putchar(' ');
	}
}
