/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:46:42 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:46:45 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

char	*get_c(va_list arg)
{
	char    *s;

	s = (char *)malloc(2);
	s[0] = (char)va_arg(arg, int);
	s[1] = '\0';
	return (s);
}

char	*get_s(t_flag flags, va_list arg)
{
	char    *s;

	if (!(s = ft_strdup(va_arg(arg, char *))))
		s = ft_strdup("(null)");
	if (flags.precision >= 0 && flags.precision < (int)ft_strlen(s))
		return (ft_strsub(s, 0, flags.precision));
	else
		return (s);
}

char	*get_f(t_flag flags, va_list arg)
{
	char    *bits;
	int     exp;
	char    *s;

	bits = get_bits_f(va_arg(arg, double));
	exp = get_exponent_f(bits);
	if (flags.precision == -1)
		s = round_num(get_int_part_f(exp, bits), get_fract_part_f(exp, bits), 6);
	else
		s = round_num(get_int_part_f(exp, bits), get_fract_part_f(exp, bits), flags.precision);
	return ((bits[0] == '1') ? ft_strjoin("-", s) : s);
}

char	*get_lf(t_flag flags, va_list arg)
{
	char    *bits;
	int     exp;
	char    *s;

	bits = get_bits_lf(va_arg(arg, long double));
	exp = get_exponent_lf(bits);
	if (flags.precision == -1)
		s = round_num(get_int_part_lf(exp, bits), get_fract_part_lf(exp, bits), 6);
	else
		s = round_num(get_int_part_lf(exp, bits), get_fract_part_lf(exp, bits), flags.precision);
	return ((bits[0] == '1') ? ft_strjoin("-", s) : s);
}

char	*get_arg(t_flag flags, va_list arg)
{
	t_func  funcs;

	if (flags.conversion == '%')
		return ("%");
	if (ft_strchr("cC", flags.conversion))
		return (get_c(arg));
	if (ft_strchr("sS", flags.conversion))
		return (get_s(flags, arg));
	if (flags.conversion == 'p')
		return (ft_ptoa(va_arg(arg, void *)));
	if (ft_strchr("dDiuUoOxX", flags.conversion))
	{
		fill_num_funcs_x(&funcs, flags, arg);
		return (get_num(flags, funcs));
	}
	if (ft_strchr("fF", flags.conversion) && !flags.lf)
		return (get_f(flags, arg));
	if (ft_strchr("fF", flags.conversion) && flags.lf)
		return (get_lf(flags, arg));
	return ("");
}