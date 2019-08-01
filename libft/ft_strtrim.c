/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:36:53 by uhand             #+#    #+#             */
/*   Updated: 2018/12/13 14:36:55 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	space_indexes(char const *s, size_t len, size_t *st, size_t *en)
{
	*st = 0;
	*en = len - 1;
	while ((s[*st] == ' ' || s[*st] == '\n' || s[*st] == '\t') && *st < *en)
		*st = *st + 1;
	while ((s[*en] == ' ' || s[*en] == '\n' || s[*en] == '\t') && *en > *st)
		*en = *en - 1;
}

static char	*make_trim(char const *s, size_t start, size_t end)
{
	char	*trim;
	size_t	size;

	size = end + 2 - start;
	if (!(trim = (char*)malloc(sizeof(*trim) * (size))))
		return (NULL);
	trim[size - 1] = '\0';
	while (size >= 2)
	{
		trim[size - 2] = (char)s[start + size - 2];
		size--;
	}
	return (trim);
}

char		*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*trim;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (len == 0)
		return (trim = ft_strnew(0));
	space_indexes(s, len, &start, &end);
	if (s[start] != ' ' && s[start] != '\n' && s[start] != '\t')
		trim = make_trim(s, start, end);
	else
		trim = ft_strnew(0);
	return (trim);
}
