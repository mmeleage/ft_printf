/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:46:56 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:46:56 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

void	print_plus_space(t_flag flags, char **s, int *count, int *len)
{
	if (flags.plus && ft_strchr("dDifF", flags.conversion) && *s[0] != '-')
	{
		ft_putchar('+');
		(*count)++;
	}
	if (flags.space && !flags.plus && ft_strchr("dDifF", flags.conversion)\
	&& *s[0] != '-')
	{
		ft_putchar(' ');
		(*count)++;
	}
	if (*s[0] == '-' && ft_strchr("dDifF", flags.conversion))
	{
		ft_putchar('-');
		(*count)++;
		(*len)--;
		(*s)++;
	}
}

void	print_p_sharp(t_flag flags, int *count, int len, char *s)
{
	if (flags.conversion == 'p')
	{
		ft_putstr("0x");
		(*count) += 2;
	}
	if (flags.sharp && ((flags.precision < len && ft_strchr("oO", flags.conversion)) || \
	ft_strchr("xX", flags.conversion)) && (s[0] != '0' || (s[0] == '0' && !flags.precision \
	&& ft_strchr("oO", flags.conversion))))
	{
		ft_putchar('0');
		if (ft_strchr("xX", flags.conversion))
		{
			ft_putchar(flags.conversion);
			(*count)++;
		}
		(*count)++;
	}
}

void	print_zero_precision(t_flag flags, int len, int *count)
{
	int		i;

	if (((ft_strchr("dDioOuUxX", flags.conversion) && flags.precision < 0) || \
	ft_strchr("fF", flags.conversion)) && flags.zero && !flags.minus)
	{
		i = flags.width - len - *count;
		if (i > 0)
			(*count) += i;
		while (i-- > 0)
			ft_putchar('0');
	}
	if (ft_strchr("dDipoOuUxX", flags.conversion) && flags.precision >= 0)
	{
		i = flags.precision - len;
		if (i > 0)
			(*count) += i;
		while (i-- > 0)
			ft_putchar('0');
	}
}

void	print_arg(t_flag flags, char *s, int *count, int len)
{
	if (!(!flags.precision && ft_strchr("dDipuUoOxX", flags.conversion) &&\
	s[0] == '0') || ft_strchr("fF", flags.conversion))
	{
		ft_putstr(s);
		(*count) += len;
	}
	if (flags.conversion == 'c' && !s[0])
		ft_putchar(s[0]);
	if (flags.sharp && ft_strchr("fF", flags.conversion) && !ft_strchr(s, '.'))
	{
		ft_putchar('.');
		(*count)++;
	}
}

int		print_arg_with_flags(t_flag flags, va_list arg)
{
	char    *s;
	int     count;
	int     len;
	int     spaces_to_width;

	count = 0;
	s = get_arg(flags, arg);
	len = ft_strlen(s);
	if (flags.conversion == 'c' && !s[0])
		len++;
	spaces_to_width = count_spaces_to_width(flags, len, s);
	print_spaces_left(flags, spaces_to_width);
	print_plus_space(flags, &s, &count, &len);
	print_p_sharp(flags, &count, len, s);
	print_zero_precision(flags, len, &count);
	print_arg(flags, s, &count, len);
	print_spaces_right(flags, spaces_to_width);
	if (spaces_to_width > 0)
		count += spaces_to_width;
	return (count);
}