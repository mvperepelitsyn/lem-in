/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 18:29:47 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 16:52:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	norma_free(t_njoin *j)
{
	if (j->i > 1)
		free(j->buf_1);
}

char		*ft_nstrjoin(int n, ...)
{
	t_njoin	j;

	if (n < 1)
		return (NULL);
	va_start(j.ap, n);
	if (n == 1)
	{
		j.buf_1 = va_arg(j.ap, char*);
		return (ft_strdup(j.buf_1));
	}
	j.i = 0;
	j.str = va_arg(j.ap, char*);
	while (++j.i < n)
	{
		j.buf_1 = j.str;
		j.buf_2 = va_arg(j.ap, char*);
		if (!(j.str = ft_strjoin(j.buf_1, j.buf_2)))
		{
			norma_free(&j);
			return (NULL);
		}
		norma_free(&j);
	}
	va_end(j.ap);
	return (j.str);
}
