# include "ft_printf.h"

void	fill_num_funcs_d(t_func *funcs, t_flag flags, va_list arg)
{
	if (ft_strchr("dDi", flags.conversion))
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
}

void	fill_num_funcs_u(t_func *funcs, t_flag flags, va_list arg)
{
	if (ft_strchr("uU", flags.conversion))
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

void	fill_num_funcs_o(t_func *funcs, t_flag flags, va_list arg)
{
	if (ft_strchr("oO", flags.conversion))
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
}

void	fill_num_funcs_x(t_func *funcs, t_flag flags, va_list arg)
{
	fill_num_funcs_d(funcs, flags, arg);
	fill_num_funcs_u(funcs, flags, arg);
	fill_num_funcs_o(funcs, flags, arg);
	if (ft_strchr("xX", flags.conversion))
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
