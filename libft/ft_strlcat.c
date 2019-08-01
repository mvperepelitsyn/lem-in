/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:43:15 by uhand             #+#    #+#             */
/*   Updated: 2018/12/18 13:43:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	while (i < size && dst[i] != '\0')
		i++;
	len += i;
	if (!(size == 0 || size < ft_strlen(dst)))
	{
		while (i < (size - 1) && src[0] != '\0')
		{
			dst[i] = (char)src[0];
			i++;
			src++;
		}
		dst[i] = '\0';
	}
	return (len);
}
