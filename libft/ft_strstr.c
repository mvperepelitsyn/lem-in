/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:18:23 by uhand             #+#    #+#             */
/*   Updated: 2018/12/06 14:18:25 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len_h;
	size_t	len_n;
	size_t	i;
	char	*addr;

	len_h = ft_strlen(haystack);
	len_n = ft_strlen(needle);
	i = 0;
	addr = (char*)haystack;
	if (len_n == 0)
		return (addr);
	if (len_n > len_h)
		return (NULL);
	while (i <= (len_h - len_n))
	{
		if (haystack[i] == needle[0])
			if (ft_strnequ(&(addr[i]), needle, len_n))
				return (&(addr[i]));
		i++;
	}
	return (NULL);
}
