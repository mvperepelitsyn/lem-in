/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:44:06 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/31 17:19:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char*)s;
	while (str[i])
	{
		if (str[i] == c)
			j = i;
		i++;
	}
	if (str[i] == '\0' && c == 0)
		return (str + i);
	else if (j > 0 || (j == 0 && s[j] == c))
		return (str + j);
	return (NULL);
}
