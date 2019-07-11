/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:55:20 by dfrost-a          #+#    #+#             */
/*   Updated: 2018/12/06 14:49:05 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*sd;
	char	*ss;
	size_t	i;

	if (dst == src)
		return (dst);
	ss = (char *)src;
	sd = (char *)dst;
	i = 0;
	if (src < dst)
		while (len-- > 0)
			sd[len] = ss[len];
	else
	{
		while (i < len)
		{
			sd[i] = ss[i];
			i++;
		}
	}
	return (dst);
}
