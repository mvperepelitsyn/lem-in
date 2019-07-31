/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:44:08 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/31 17:19:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	str = NULL;
	if (s1 && s2)
	{
		i = ft_strlen((char *)s1);
		j = ft_strlen((char *)s2);
		str = (char*)malloc(sizeof(char) * (i + j + 1));
		if (str)
		{
			str[i + j] = '\0';
			while (--j >= 0)
				str[i + j] = s2[j];
			while (--i >= 0)
				str[i] = s1[i];
		}
	}
	return (str);
}
