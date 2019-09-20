/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 15:32:52 by uhand             #+#    #+#             */
/*   Updated: 2019/07/24 20:30:50 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstaddnext(t_list **alst, void const *content, size_t content_size)
{
	t_list	*tmplst;
	t_list	*l_ptr;

	if (!alst)
		return (0);
	if (!(tmplst = ft_lstnew(content, content_size)))
		return (-1);
	if (alst[0] == NULL)
	{
		alst[0] = tmplst;
		return (1);
	}
	l_ptr = alst[0];
	while (l_ptr->next != NULL)
		l_ptr = l_ptr->next;
	l_ptr->next = tmplst;
	return (1);
}
