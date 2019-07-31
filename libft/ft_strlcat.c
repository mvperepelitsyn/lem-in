/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:25:37 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/31 17:19:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	si;
	size_t	di;

	dlen = ft_strnlen(dst, size);
	slen = ft_strlen(src);
	if (dlen < size)
	{
		si = 0;
		di = dlen;
		while (di < size && si < slen)
			dst[di++] = src[si++];
		if (di < size)
			dst[di] = '\0';
		else
			dst[size - 1] = '\0';
	}
	return (dlen + slen);
}
