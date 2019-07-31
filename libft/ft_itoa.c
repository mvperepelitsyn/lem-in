/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:13:24 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/31 17:19:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_elem_count(int n)
{
	int k;

	k = 0;
	if (n < 0)
		k++;
	if (n == 0)
		k++;
	while (n != 0)
	{
		n = n / 10;
		k++;
	}
	return (k);
}

static	char	*fillstr(char *str, int k, int n)
{
	while (k >= 0 && n != 0)
	{
		str[k] = n % 10 + 48;
		n = n / 10;
		k--;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		k;

	k = ft_elem_count(n);
	str = (char*)malloc(sizeof(char) * (k + 1));
	if (str == NULL)
		return (NULL);
	str[k--] = '\0';
	if (n == 0)
	{
		str[k] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[k] = '8';
			n = n / 10;
			k--;
		}
		n = n * (-1);
	}
	return (fillstr(str, k, n));
}
