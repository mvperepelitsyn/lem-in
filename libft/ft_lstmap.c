/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 17:16:04 by uhand             #+#    #+#             */
/*   Updated: 2018/12/24 17:16:06 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	void	(*del)(void*, size_t);
	t_list	*start_list;
	t_list	*list;
	t_list	*next_list;

	if (!lst || !f || !(start_list = f(lst)))
		return (NULL);
	del = &ft_lstfree;
	list = start_list;
	lst = lst->next;
	while (lst)
	{
		if (!(next_list = f(lst)))
		{
			ft_lstdel(&start_list, del);
			return (NULL);
		}
		list->next = next_list;
		list = next_list;
		lst = lst->next;
	}
	list->next = NULL;
	return (start_list);
}
