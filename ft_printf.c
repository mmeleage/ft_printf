# include "ft_printf.h"

int     is_conversion(char c)
{
    char    conversions[] = "cCsSpdDioOuUxXfF%";
    return (ft_strchr(conversions, c) ? 1 : 0);
}

int     is_flag(char c)
{
    char    flags[] = "+-0# ";
    return (ft_strchr(flags, c) ? 1 : 0);
}

int     is_size(char c)
{
    char    sizes[] = "lLh";
    return (ft_strchr(sizes, c) ? 1 : 0);
}

void    initialize_flags(t_flag *flags)
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

t_flag    fill_flags(char c, int *j, t_flag flags)
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

t_flag  fill_sizes(char *format, int *j, t_flag flags)
{
    if (format[*j] == 'h' && format[*j + 1] != 'h')
    {
        if (!flags.l)
            flags.h = 1;
        (*j) += 1;
    }
    else if (format[*j] == 'h' && format[*j + 1] == 'h')
    {
        if (!flags.l)
            flags.h = 2;
        (*j) += 2;
    }
    else if (format[*j] == 'l' && format[*j + 1] != 'l')
    {
        if (format[*j + 1] != 'L')
        {
            flags.l = 1;
            flags.h = 0;
        }
        (*j) += 1;
    }
    else if (format[*j] == 'l' && format[*j + 1] == 'l')
    {
        flags.l = 2;
        flags.h = 0;
        (*j) += 2;
    }
    else if (format[*j] == 'L' && ft_strchr("fF", format[*j + 1]))
    {
        flags.lf = 1;
        (*j) += 1;
    }
    else
        (*j) += 1;
    return (flags);
}

void    fill_num_funcs(t_func *funcs, t_flag flags, va_list arg)
{
    if (flags.conversion == 'd' || flags.conversion == 'D' || flags.conversion == 'i')
    {
        if (flags.h == 2)
            (*funcs).hhs = ft_itoa_hh((char)va_arg(arg, int));
        if (flags.h == 1)
            (*funcs).hs = ft_itoa_h((short int)va_arg(arg, int));
        if (flags.l == 2)
            (*funcs).lls = ft_itoa_ll(va_arg(arg, long long int));
        if (flags.l == 1)
            (*funcs).ls = ft_itoa_l(va_arg(arg, long int));
        if (!flags.h && !flags.l)
            (*funcs).s = ft_itoa(va_arg(arg, int));
    }
    if (flags.conversion == 'u' || flags.conversion == 'U')
    {
        if (flags.h == 2)
            (*funcs).hhs = ft_itoa_hhu((unsigned char)va_arg(arg, unsigned int), 10, flags.conversion);
        if (flags.h == 1)
            (*funcs).hs = ft_itoa_hu((unsigned short int)va_arg(arg, unsigned int), 10, flags.conversion);
        if (flags.l == 2)
            (*funcs).lls = ft_itoa_llu(va_arg(arg, unsigned long long int), 10, flags.conversion);
        if (flags.l == 1)
            (*funcs).ls = ft_itoa_lu(va_arg(arg, unsigned long int), 10, flags.conversion);
        if (!flags.h && !flags.l)
            (*funcs).s = ft_itoa_u(va_arg(arg, unsigned int), 10, flags.conversion);
    }
}

void    fill_oxnum_funcs(t_func *funcs, t_flag flags, va_list arg)
{
    if (flags.conversion == 'o' || flags.conversion == 'O')
    {
        if (flags.h == 2)
            (*funcs).hhs = ft_itoa_hhu((unsigned char)va_arg(arg, unsigned int), 8, flags.conversion);
        if (flags.h == 1)
            (*funcs).hs = ft_itoa_hu((unsigned short int)va_arg(arg, unsigned int), 8, flags.conversion);
        if (flags.l == 2)
            (*funcs).lls = ft_itoa_llu(va_arg(arg, unsigned long long int), 8, flags.conversion);
        if (flags.l == 1)
            (*funcs).ls = ft_itoa_lu(va_arg(arg, unsigned long int), 8, flags.conversion);
        if (!flags.h && !flags.l)
            (*funcs).s = ft_itoa_u(va_arg(arg, unsigned int), 8, flags.conversion);
    }
    if (flags.conversion == 'x' || flags.conversion == 'X')
    {
        if (flags.h == 2)
            (*funcs).hhs = ft_itoa_hhu((unsigned char)va_arg(arg, unsigned int), 16, flags.conversion);
        if (flags.h == 1)
            (*funcs).hs = ft_itoa_hu((unsigned short int)va_arg(arg, unsigned int), 16, flags.conversion);
        if (flags.l == 2)
            (*funcs).lls = ft_itoa_llu(va_arg(arg, unsigned long long int), 16, flags.conversion);
        if (flags.l == 1)
            (*funcs).ls = ft_itoa_lu(va_arg(arg, unsigned long int), 16, flags.conversion);
        if (!flags.h && !flags.l)
            (*funcs).s = ft_itoa_u(va_arg(arg, unsigned int), 16, flags.conversion);
    }
}

char    *get_num(t_flag flags, t_func funcs)
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

char    *get_arg(t_flag flags, va_list arg)
{
    char    *s;
    t_func  funcs;
    char    *bits;
    int     exp;

    if (flags.conversion == '%')
        return ("%");
    if (ft_strchr("cC", flags.conversion))
    {
        s = (char *)malloc(2);
        s[0] = (char)va_arg(arg, int);
        s[1] = '\0';
        return (s);
    }
    if (ft_strchr("sS", flags.conversion))
    {
        if (!(s = ft_strdup(va_arg(arg, char *))))
            s = ft_strdup("(null)");
        if (flags.precision >= 0 && flags.precision < (int)ft_strlen(s))
            return (ft_strsub(s, 0, flags.precision));
        else
            return (s);
    }
    if (flags.conversion == 'p')
        return (ft_ptoa(va_arg(arg, void *)));
    if (ft_strchr("dDiuUoOxX", flags.conversion))
    {
        fill_num_funcs(&funcs, flags, arg);
        fill_oxnum_funcs(&funcs, flags, arg);
        return (get_num(flags, funcs));
    }
    if (ft_strchr("fF", flags.conversion))
    {
        if (flags.lf)
        {
            bits = get_bits_lf(va_arg(arg, long double));
            exp = get_exponent_lf(bits);
            if (flags.precision == -1)
                s = round_num(get_int_part_lf(exp, bits), get_fract_part_lf(exp, bits), 6);
            else
                s = round_num(get_int_part_lf(exp, bits), get_fract_part_lf(exp, bits), flags.precision);
            return ((bits[0] == '1') ? ft_strjoin("-", s) : s);
        }
        else
        {
            bits = get_bits_f(va_arg(arg, double));
            exp = get_exponent_f(bits);
            if (flags.precision == -1)
                s = round_num(get_int_part_f(exp, bits), get_fract_part_f(exp, bits), 6);
            else
                s = round_num(get_int_part_f(exp, bits), get_fract_part_f(exp, bits), flags.precision);
            return ((bits[0] == '1') ? ft_strjoin("-", s) : s);
        }
    }
    return ("");
}

int     count_spaces_to_width(t_flag flags, int len, char *s)
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
        if (flags.sharp)
        {
            if ((s[0] != '0' && ft_strchr("oO", flags.conversion)) ||\
            ft_strchr("fF", flags.conversion))
                spaces_to_width--;
            if (s[0] != '0' && ft_strchr("xX", flags.conversion))
                spaces_to_width -= 2;
        }
        if (flags.conversion == 'p')
            spaces_to_width -= 2;
        if (flags.zero && flags.precision == -1 && !flags.minus)
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

int    print_arg_with_flags(t_flag flags, va_list arg)
{
    char    *s;
    int     count;
    int     i;
    int     len;
    int     spaces_to_width;

    count = 0;
    s = get_arg(flags, arg);
    len = ft_strlen(s);
    if (flags.conversion == 'c' && !s[0])
        len++;
    spaces_to_width = count_spaces_to_width(flags, len, s);
    if (!flags.minus)
    {
        i = spaces_to_width;
        while (i-- > 0)
            ft_putchar(' ');
    }
    if (flags.plus && ft_strchr("dDifF", flags.conversion) && s[0] != '-')
    {
        ft_putchar('+');
        count++;
    }
    if (flags.space && !flags.plus && ft_strchr("dDifF", flags.conversion)\
    && s[0] != '-')
    {
        ft_putchar(' ');
        count++;
    }
    if (s[0] == '-' && ft_strchr("dDifF", flags.conversion))
    {
        ft_putchar('-');
        count++;
        len--;
        s++;
    }
    if (flags.conversion == 'p')
    {
        ft_putstr("0x");
        count += 2;
    }
    if (flags.sharp && ft_strchr("oOxX", flags.conversion) && s[0] != '0')
    {
        ft_putchar('0');
        if (ft_strchr("xX", flags.conversion))
        {
            ft_putchar(flags.conversion);
            count++;
        }
        count++;
    }
    if (((ft_strchr("dDioOuUxX", flags.conversion) && flags.precision == -1) || \
    ft_strchr("fF", flags.conversion)) && flags.zero && !flags.minus)
    {
        i = flags.width - len - count;
        if (i > 0)
            count += i;
        while (i-- > 0)
            ft_putchar('0');
    }
    if (ft_strchr("dDipoOuUxX", flags.conversion) && flags.precision != -1)
    {
        i = flags.precision - len;
        if (i > 0)
            count += i;
        while (i-- > 0)
            ft_putchar('0');
    }
    if (!(!flags.precision && ft_strchr("dDipuUoOxX", flags.conversion) &&\
    s[0] == '0') || ft_strchr("fF", flags.conversion))
    {
        ft_putstr(s);
        count += len;
    }
    if (flags.conversion == 'c' && !s[0])
        ft_putchar(s[0]);
    if (flags.sharp && ft_strchr("fF", flags.conversion) && !ft_strchr(s, '.'))
    {
        ft_putchar('.');
        count++;
    }
    if (flags.minus)
    {
        i = spaces_to_width;
        while (i-- > 0)
            ft_putchar(' ');
    }
    if (spaces_to_width > 0)
        count += spaces_to_width;
    return (count);
}

int     ft_printf(const char *restrict format, ...)
{
    va_list     arg;
    t_flag      flags;
    int         i;
    int         j;
    int         count;

    count = 0;
    i = 0;
    va_start(arg, format);
    while (format[i])
    {
        initialize_flags(&flags);
        if (format[i] == '%')
        {
            j = i + 1;
            while ((is_conversion(format[j]) || is_flag(format[j]) || format[j] == '*'\
            || is_size(format[j]) || ft_isdigit(format[j]) || format[j] == '.')\
            && format[j])
            {
                if (is_flag(format[j]))
                    flags = fill_flags(format[j], &j, flags);
                else if (ft_isdigit(format[j]) && format[j - 1] != '.')
                {
                    flags.width = ft_atoi(format + j);
                    while (ft_isdigit(format[j]))
                        j++;
                }
                else if (format[j] == '*' && format[j - 1] != '.')
                {
                    flags.width = va_arg(arg, int);
                    if (flags.width < 0)
                    {
                        flags.width = -flags.width;
                        flags.minus = 1;
                    }
                    j++;
                }
                else if (format[j] == '.')
                {
                    if (ft_isdigit(format[j + 1]))
                    {
                        flags.precision = ft_atoi(format + j + 1);
                        j++;
                        while (ft_isdigit(format[j]))
                            j++;
                    }
                    else if (format[j + 1] == '*')
                    {
                        flags.precision = va_arg(arg, int);
                        j += 2;
                    }
                    else
                    {
                        flags.precision = 0;
                        j++;
                    }
                }
                else if (is_size(format[j]))
                    flags = fill_sizes((char *)format, &j, flags);
                else if (is_conversion(format[j]))
                {
                    flags.conversion = format[j++];
                    break;
                }
            }
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
    va_end(arg);
    return (count);
}

int     main()
{
    printf("{%05.*d}", -15, 42);
    ft_printf("{%05.*d}", -15, 42);
    return (0);
}