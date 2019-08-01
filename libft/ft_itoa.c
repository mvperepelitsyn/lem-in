/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:20:05 by uhand             #+#    #+#             */
/*   Updated: 2018/12/15 14:20:08 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_string(char **str, unsigned int num, int order, int i)
{
	if (num == 0)
	{
		str[0][0] = '0';
		return ;
	}
	while (order > 0)
	{
		str[0][order + i - 1] = (num % 10) + 48;
		num /= 10;
		order--;
	}
}

char		*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	int				order;

	if (n < 0)
		num = (unsigned int)(-n);
	else
		num = (unsigned int)n;
	order = ft_order(num);
	if (n < 0)
		order++;
	if (!(str = ft_strnew(order)))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		order--;
		n = 1;
	}
	else
		n = 0;
	set_string(&str, num, order, n);
	return (str);
}
