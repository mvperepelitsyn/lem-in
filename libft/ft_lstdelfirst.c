/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 15:32:38 by uhand             #+#    #+#             */
/*   Updated: 2019/01/06 15:32:40 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelfirst(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmplst;

	if (!alst || !*alst || !del)
		return ;
	tmplst = alst[0]->next;
	ft_lstdelone(alst, del);
	*alst = tmplst;
}
