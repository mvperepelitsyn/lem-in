/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:17:08 by dfrost-a          #+#    #+#             */
/*   Updated: 2018/12/05 14:54:23 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
		int c, size_t n)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*desnt;

	i = 0;
	source = (unsigned char*)src;
	desnt = (unsigned char*)dst;
	while (i < n)
	{
		desnt[i] = source[i];
		if (source[i] == (unsigned char)c)
			return (desnt + i + 1);
		i++;
	}
	return (NULL);
}
