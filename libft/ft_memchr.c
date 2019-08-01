/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:42:40 by uhand             #+#    #+#             */
/*   Updated: 2018/12/11 16:42:43 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*area;
	unsigned char	chr;
	size_t			i;

	area = (unsigned char*)s;
	chr = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (area[i] == chr)
			return ((void*)(s + i));
		i++;
	}
	return (NULL);
}
