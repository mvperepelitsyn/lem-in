/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:30:15 by uhand             #+#    #+#             */
/*   Updated: 2018/12/13 11:30:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char const *s1, char const *s2, size_t l1, size_t l2)
{
	char	*j;
	size_t	i;

	if (!(j = (char*)malloc(sizeof(*j) * (l1 + l2 + 1))))
		return (NULL);
	j[l1 + l2] = '\0';
	i = 0;
	while (i < l1)
	{
		j[i] = (char)s1[i];
		i++;
	}
	while (l2 > 0)
	{
		j[l1 + l2 - 1] = (char)s2[l2 - 1];
		l2--;
	}
	return (j);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*j;

	l1 = 0;
	l2 = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s2 == NULL && s1 != NULL)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	j = join(s1, s2, l1, l2);
	return (j);
}
