/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:46:30 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 19:40:00 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag	ft_printf_precision(t_flag flags, va_list arg, char *format, int *j)
{
	if (ft_isdigit(format[*j + 1]))
	{
		flags.precision = ft_atoi(format + *j + 1);
		(*j)++;
		while (ft_isdigit(format[*j]))
			(*j)++;
	}
	else if (format[*j + 1] == '*')
	{
		flags.precision = va_arg(arg, int);
		(*j) += 2;
	}
	else
	{
		flags.precision = 0;
		(*j)++;
	}
	return (flags);
}

t_flag	ft_printf_width(t_flag flags, va_list arg, int *j)
{
	flags.width = va_arg(arg, int);
	if (flags.width < 0)
	{
		flags.width = -flags.width;
		flags.minus = 1;
	}
	(*j)++;
	return (flags);
}

t_flag	ft_printf_flags(char *format, int *j, t_flag flags, va_list arg)
{
	while ((is_conversion(format[*j]) || is_flag(format[*j]) || format[*j] == '*'\
	|| is_size(format[*j]) || ft_isdigit(format[*j]) || format[*j] == '.')\
	&& format[*j])
	{
		if (is_flag(format[*j]))
			flags = fill_flags(format[*j], j, flags);
		else if (ft_isdigit(format[*j]) && format[*j - 1] != '.')
		{
			flags.width = ft_atoi(format + *j);
			while (ft_isdigit(format[*j]))
				(*j)++;
		}
		else if (format[*j] == '*' && format[*j - 1] != '.')
			flags = ft_printf_width(flags, arg, j);
		else if (format[*j] == '.')
			flags = ft_printf_precision(flags, arg, (char *)format, j);
		else if (is_size(format[*j]))
			flags = fill_sizes_l((char *)format, j, flags);
		else if (is_conversion(format[*j]))
		{
			flags.conversion = format[(*j)++];
			break ;
		}
	}
	return (flags);
}

int		ft_printf_count(char *format, t_flag flags, va_list arg, int count)
{
	int		i;
	int		j;

	i = 0;
	while (format[i])
	{
		initialize_flags(&flags);
		if (format[i] == '%')
		{
			j = i + 1;
			flags = ft_printf_flags(format, &j, flags, arg);
			count += print_arg_with_flags(flags, arg);
			if (!format[j])
				break ;
			else
				i = j;
		}
		else
		{
			ft_putchar(format[i++]);
			count++;
		}
	}
	return (count);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list	arg;
	t_flag	flags;
	int		count;

	count = 0;
	va_start(arg, format);
	initialize_flags(&flags);
	count = ft_printf_count((char *)format, flags, arg, count);
	va_end(arg);
	return (count);
}
