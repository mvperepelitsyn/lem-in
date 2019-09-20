/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:54:53 by uhand             #+#    #+#             */
/*   Updated: 2019/05/28 18:34:08 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_arrjoin(char **arr, int len)
{
	size_t	s_len;
	size_t	j;
	int		i;
	char	*str;

	if (len < 1)
		return (NULL);
	s_len = 0;
	i = -1;
	while (++i < len)
		s_len += ft_strlen(arr[i]);
	if (!(str = ft_strnew(s_len + (len - 1))))
		return (NULL);
	i = -1;
	s_len = -1;
	while (++i < len)
	{
		j = -1;
		while (arr[i][++j] != '\0')
			str[++s_len] = arr[i][j];
		if (i != (len - 1))
			str[++s_len] = ' ';
	}
	return (str);
}
