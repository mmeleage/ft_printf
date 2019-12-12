# include "ft_printf.h"

int		count_digits_l(long int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa_l(long int n)
{
	char	*str;
	int		i;
	int		len;

	len = count_digits_l(n);
	i = (n < 0) ? len : (len - 1);
	str = (char *)malloc(i + 2);
	if (n == 0)
		str[0] = '0';
	str[i + 1] = '\0';
	if (n < 0)
		str[0] = '-';
	while (n)
	{
		str[i--] = (n < 0) ? (-(n % 10) + '0') : (n % 10 + '0');
		n /= 10;
	}
	return (str);
}
