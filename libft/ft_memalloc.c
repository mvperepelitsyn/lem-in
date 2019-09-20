/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:46:33 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 14:05:23 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*area;

	if (size == 0)
		return (NULL);
	if (!(area = (void*)malloc(sizeof(*area) * size)))
		return (NULL);
	while (size > 0)
	{
		area[size - 1] = 0;
		size--;
	}
	return (area);
}
