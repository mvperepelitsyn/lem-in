/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllcpyr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:51:30 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 17:14:06 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dllist	*ft_dllcpyr(t_dllist *src, t_dllist *dst)
{
	t_dllist	*tmp;
	t_dllist	*prev;

	if (!src)
		return (NULL);
	if (!(dst = ft_dllnew(src->content, src->content_size)))
		return (NULL);
	prev = dst;
	src = src->right;
	while (src)
	{
		if (!(tmp = ft_dllnew(src->content, src->content_size)))
		{
			ft_dlldel(&dst, &ft_lstfree);
			return (NULL);
		}
		prev->right = tmp;
		tmp->left = prev;
		tmp = tmp->right;
		prev = prev->right;
		src = src->right;
	}
	return (dst);
}
