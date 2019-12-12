# include "ft_printf.h"

int		is_conversion(char c)
{
	char    conversions[] = "cCsSpdDioOuUxXfF%";
	return (ft_strchr(conversions, c) ? 1 : 0);
}

int		is_flag(char c)
{
	char    flags[] = "+-0# ";
	return (ft_strchr(flags, c) ? 1 : 0);
}

int		is_size(char c)
{
	char    sizes[] = "lLh";
	return (ft_strchr(sizes, c) ? 1 : 0);
}

char	*get_num(t_flag flags, t_func funcs)
{
	if (flags.h == 2)
		return (funcs.hhs);
	if (flags.h == 1)
		return (funcs.hs);
	if (flags.l == 2)
		return (funcs.lls);
	if (flags.l == 1)
		return (funcs.ls);
	return (funcs.s);
}

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
	int     spaces_to_width;

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
			break;
		}
	}
	return (flags);
}

int		ft_printf_count(char *format, t_flag flags, va_list arg, int count)
{
	int         i;
	int         j;

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
				break;
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
	va_list     arg;
	t_flag      flags;
	int         count;

	count = 0;
	va_start(arg, format);
	initialize_flags(&flags);
	count = ft_printf_count((char *)format, flags, arg, count);
	va_end(arg);
	return (count);
}
