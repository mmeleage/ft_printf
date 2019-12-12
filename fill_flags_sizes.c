/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_flags_sizes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:45:22 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:45:23 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

void	initialize_flags(t_flag *flags)
{
	(*flags).minus = 0;
	(*flags).plus = 0;
	(*flags).zero = 0;
	(*flags).space = 0;
	(*flags).sharp = 0;
	(*flags).width = 0;
	(*flags).precision = -1;
	(*flags).h = 0;
	(*flags).l = 0;
	(*flags).conversion = '0';
	(*flags).lf = 0;
}

t_flag	fill_flags(char c, int *j, t_flag flags)
{
	if (c == '-')
		flags.minus = 1;
	if (c == '+')
		flags.plus = 1;
	if (c == '0')
		flags.zero = 1;
	if (c == ' ')
		flags.space = 1;
	if (c == '#')
		flags.sharp = 1;
	(*j) += 1;
	return (flags);
}

t_flag	fill_sizes_h(char *format, int *j, t_flag flags)
{
	if (format[*j] == 'h' && format[*j + 1] != 'h')
	{
		if (!flags.l)
			flags.h = 1;
		(*j) += 1;
	}
	if (format[*j] == 'h' && format[*j + 1] == 'h')
	{
		if (!flags.l)
			flags.h = 2;
		(*j) += 2;
	}
	return (flags);
}

t_flag	fill_sizes_l(char *format, int *j, t_flag flags)
{
	flags = fill_sizes_h(format, j, flags);
	if (format[*j] == 'l' && format[*j + 1] != 'l')
	{
		if (format[*j + 1] != 'L')
		{
			flags.l = 1;
			flags.h = 0;
		}
		(*j) += 1;
	}
	if (format[*j] == 'l' && format[*j + 1] == 'l')
	{
		flags.l = 2;
		flags.h = 0;
		(*j) += 2;
	}
	if (format[*j] == 'L')
	{
		if (ft_strchr("fF", format[*j + 1]))
			flags.lf = 1;
		(*j) += 1;
	}
	return (flags);
}
