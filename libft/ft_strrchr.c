/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 12:13:58 by uhand             #+#    #+#             */
/*   Updated: 2018/12/06 12:14:02 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*a;

	i = ft_strlen(s);
	a = (char*)s;
	while (i != 0)
	{
		if (s[i] == c)
			return (a + i);
		i--;
	}
	if (s[i] == c)
		return (a + i);
	return (0);
}
