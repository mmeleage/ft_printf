/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <mmeleage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:44:45 by mmeleage          #+#    #+#             */
/*   Updated: 2019/12/12 18:44:47 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

int		is_conversion(char c)
{
	return (ft_strchr("cCsSpdDioOuUxXfF%", c) ? 1 : 0);
}

int		is_flag(char c)
{
	return (ft_strchr("+-0# ", c) ? 1 : 0);
}

int		is_size(char c)
{
	return (ft_strchr("lLh", c) ? 1 : 0);
}