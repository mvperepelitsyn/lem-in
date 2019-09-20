/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitspaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:06:31 by uhand             #+#    #+#             */
/*   Updated: 2019/05/28 19:05:08 by uhand            ###   ########.fr       */
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

static char		*set_string(char const *s, size_t *s_i)
{
	char	*str;
	size_t	len;

	len = 0;
	while (ft_isspace(s[*s_i]))
		*s_i = *s_i + 1;
	while (!ft_isspace(s[*s_i + len]) && s[*s_i + len] != '\0')
		len++;
	str = ft_strsub(s, (unsigned int)*s_i, len);
	*s_i = *s_i + len;
	return (str);
}

static char		**set_arr(char const *s, size_t x)
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
		if (!(arr[x_i] = set_string(s, &s_i)))
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

static size_t	str_calc(char const *s)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	if (!ft_strlen(s))
		return (0);
	while (s[i] != '\0')
	{
		if (!ft_isspace(s[i]) && s[i] != '\0')
		{
			res++;
			while (!ft_isspace(s[i]) && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (res);
}

char			**ft_strsplitspaces(char const *s)
{
	char	**arr;
	size_t	x;

	if (s == NULL)
		return (NULL);
	if (!(x = str_calc(s)))
	{
		if (!(arr = (char**)malloc(sizeof(char*) * 1)))
			return (NULL);
		if (!(arr[0] = ft_strnew(0)))
		{
			free(arr);
			return (NULL);
		}
	}
	arr = set_arr(s, x);
	return (arr);
}
