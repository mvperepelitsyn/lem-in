/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:30:54 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 16:51:14 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *prev_a, t_list *a, t_list *prev_b, t_list *b)
{
	t_list	*tmp;

	if (!a || !b)
		return ;
	if (prev_a)
		prev_a->next = b;
	if (prev_b)
		prev_b->next = a;
	tmp = a->next;
	a->next = b->next;
	b->next = tmp;
}
