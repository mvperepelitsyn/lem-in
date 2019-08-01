/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:34:29 by uhand             #+#    #+#             */
/*   Updated: 2018/12/17 14:34:32 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;
	unsigned char	chr;
	size_t			i;

	if (n == 0)
		return (NULL);
	c_dst = (unsigned char*)dst;
	c_src = (unsigned char*)src;
	chr = (unsigned char)c;
	i = 0;
	while (i < n && c_src[i] != chr)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	if (i == n && c_dst[i - 1] != chr)
		return (NULL);
	c_dst[i] = c_src[i];
	return (&c_dst[i + 1]);
}
