/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:21:17 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 17:29:08 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dllist	*ft_dllcpy(t_dllist *src, t_dllist *dst)
{
	if (!src)
		return (NULL);
	if (!(dst = ft_dllnew(src->content, src->content_size)))
		return (NULL);
	if (src->right)
	{
		if (!(dst->right = ft_dllcpyr(src->right, dst->right)))
		{
			ft_dlldel(&dst, &ft_lstfree);
			return (NULL);
		}
		dst->right->left = dst;
	}
	if (src->left)
	{
		if (!(dst->left = ft_dllcpyr(src->left, dst->left)))
		{
			ft_dlldel(&dst, &ft_lstfree);
			return (NULL);
		}
		dst->left->right = dst;
	}
	return (dst);
}
