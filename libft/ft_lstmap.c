/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeleage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:04:12 by mmeleage          #+#    #+#             */
/*   Updated: 2019/09/18 15:12:38 by mmeleage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*new_lst_copy;

	if (lst == NULL)
		return (NULL);
	new_lst = f(lst);
	if (new_lst == NULL)
		return (NULL);
	new_lst_copy = new_lst;
	lst = lst->next;
	while (lst)
	{
		new_lst->next = f(lst);
		if (new_lst->next == NULL)
			return (NULL);
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (new_lst_copy);
}
