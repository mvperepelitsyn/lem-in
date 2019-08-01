/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:13:32 by uhand             #+#    #+#             */
/*   Updated: 2018/12/15 18:13:34 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	len;
	char	*map;

	if (s == NULL || f == NULL || !(len = ft_strlen(s)))
		return (NULL);
	i = 0;
	if (!(map = ft_strnew(len)))
		return (NULL);
	while (s[i] != '\0')
	{
		map[i] = f(s[i]);
		i++;
	}
	return (map);
}
