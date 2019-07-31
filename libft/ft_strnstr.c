/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:00:51 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/31 17:19:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	check;

	check = 0;
	while (needle[check] != '\0')
		check++;
	if (check == 0)
		return ((char*)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && ((i + j) < len))
		{
			if (j == check || j == (check - 1))
				return ((char*)haystack + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
