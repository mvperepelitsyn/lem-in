/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:46:56 by uhand             #+#    #+#             */
/*   Updated: 2019/08/01 13:25:40 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*area;

	if ((size + 1) == 0)
		return (NULL);
	if (!(area = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	size++;
	while (size > 0)
	{
		area[size - 1] = '\0';
		size--;
	}
	return (area);
}
