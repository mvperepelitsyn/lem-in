/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:06:31 by uhand             #+#    #+#             */
/*   Updated: 2018/12/13 19:06:34 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_free(char ***arr, size_t x_i)
{
	size_t	i;

	i = 0;
	while (i <= x_i)
	{
		free(arr[0][i]);
		i++;
	}
}

static char		*set_string(char const *s, char c, size_t *s_i)
{
	char	*str;
	size_t	len;

	len = 0;
	while (s[*s_i] == c)
		*s_i = *s_i + 1;
	while (s[*s_i + len] != c && s[*s_i + len] != '\0')
		len++;
	str = ft_strsub(s, (unsigned int)*s_i, len);
	*s_i = *s_i + len;
	return (str);
}

static char		**set_arr(char const *s, char c, size_t x)
{
	size_t	s_i;
	size_t	x_i;
	char	**arr;

	s_i = 0;
	x_i = 0;
	if (!(arr = (char**)malloc(sizeof(char*) * (x + 1))))
		return (NULL);
	while (x_i < x)
	{
		if (!(arr[x_i] = set_string(s, c, &s_i)))
		{
			set_free(&arr, --x_i);
			free(arr);
			return (NULL);
		}
		x_i++;
	}
	arr[x] = NULL;
	return (arr);
}

static size_t	str_calc(char const *s, char c)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	if (!ft_strlen(s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			res++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	size_t	x;

	if (s == NULL)
		return (NULL);
	if (!(x = str_calc(s, c)))
	{
		if (!(arr = (char**)malloc(sizeof(char*) * 1)))
			return (NULL);
		if (!(arr[0] = ft_strnew(0)))
		{
			free(arr);
			return (NULL);
		}
	}
	arr = set_arr(s, c, x);
	return (arr);
}
