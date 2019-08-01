/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:00:57 by uhand             #+#    #+#             */
/*   Updated: 2018/12/12 16:01:00 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	if (len == 0)
		return (s2 = ft_strnew(0));
	if (!(s2 = (char*)malloc(sizeof(*s2) * (len + 1))))
		return (NULL);
	s2[len] = (char)s1[len];
	while (len > 0)
	{
		s2[len - 1] = (char)s1[len - 1];
		len--;
	}
	return (s2);
}
