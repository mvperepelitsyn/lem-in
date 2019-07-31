/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:23:37 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/31 17:19:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**checkwords(char const *s, char **ar, char c)
{
	int	k;
	int i;

	i = 0;
	k = ft_hm_wrd((char*)s, c);
	while (ar[i] != NULL)
		i++;
	if (i != (k))
	{
		while (i >= 0)
		{
			ft_strdel(ar++);
			i--;
		}
		free(ar);
		ar = NULL;
	}
	return (ar);
}

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	size_t		j;
	size_t		l;
	char		**ar;

	i = -1;
	if (!s || !(ar = (char**)malloc(sizeof(char*) * (ft_hm_wrd(s, c) + 1))))
		return (NULL);
	l = 0;
	while (++i < (ft_hm_wrd((char*)s, c)))
	{
		j = 0;
		while (s[l] == c)
			l++;
		if (!(ar[i] = ft_strnew(ft_lentill(s + l, c) + 1)))
			ar[i] = NULL;
		while (s[l] != c && s[l])
			ar[i][j++] = s[l++];
		ar[i][j] = '\0';
	}
	ar[i] = 0;
	return (checkwords(s, ar, c));
}
