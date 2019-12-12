# include "ft_printf.h"

char	*ft_ptoa(void *p)
{
    return (ft_itoa_lu((unsigned long int)p, 16, 'x'));
}
