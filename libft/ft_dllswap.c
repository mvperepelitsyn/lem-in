/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:47:06 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 16:46:59 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dllswap(t_dllist *a, t_dllist *b)
{
	void	*content;
	size_t	size;

	if (!a || !b)
		return ;
	content = a->content;
	a->content = b->content;
	b->content = content;
	if (a->content_size == b->content_size)
		return ;
	size = a->content_size;
	a->content_size = b->content_size;
	b->content_size = size;
}
