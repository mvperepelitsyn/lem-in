/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:31:21 by uhand             #+#    #+#             */
/*   Updated: 2018/12/06 18:31:23 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_starters(size_t *i, char *s, int *sign)
{
	while (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13))
		*i = *i + 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		*i = *i + 1;
	}
	while (s[*i] == '0')
		*i = *i + 1;
}

static void	calc_result(size_t i, char *s, long long *res, size_t len)
{
	long long	order;

	order = 1;
	while (len > 0)
	{
		*res = *res + ((s[i + len - 1] - 48) * order);
		order *= 10;
		len--;
	}
}

static void	check_digits(size_t i, char *s, long long *res, int *sign)
{
	size_t		len;

	len = 0;
	while (ft_isdigit(s[i + len]))
		len++;
	if (len >= 19)
	{
		if (len > 19)
		{
			if (*sign == 1)
				*res = -1;
			return ;
		}
		if (*sign == 1)
			if (ft_strncmp(&s[i], "9223372036854775807", len) > 0)
			{
				*res = -1;
				return ;
			}
		if (*sign == -1)
			if (ft_strncmp(&s[i], "9223372036854775808", len) > 0)
				return ;
	}
	calc_result(i, s, res, len);
}

int			ft_atoi(const char *str)
{
	size_t		i;
	char		*s;
	long long	res;
	int			sign;

	i = 0;
	s = (char*)str;
	res = 0;
	sign = 1;
	if (ft_strlen(str) == 0)
		return (0);
	skip_starters(&i, s, &sign);
	if (!(ft_isdigit(s[i])))
		return (0);
	check_digits(i, s, &res, &sign);
	return ((int)res * sign);
}
