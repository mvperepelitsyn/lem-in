/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_rep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:38:58 by uhand             #+#    #+#             */
/*   Updated: 2019/05/24 20:25:57 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// static void	print_bits(size_t size, void *ptr, char space)
// {
// 	unsigned char	*b;
// 	unsigned char	byte;
// 	int				i;
// 	int				j;
//
// 	b = (unsigned char*)ptr;
// 	i = size - 1;
// 	j = 7;
// 	while (i >= 0)
// 	{
// 		while (j >= 0)
// 		{
// 			byte = (b[i] >> j) & 1;
// 			ft_putchar(byte + '0');
// 			j--;
// 		}
// 		if (space == 1)
// 			ft_putchar(' ');
// 		j = 7;
// 		i--;
// 	}
// 	ft_putchar('\n');
// }

static int	set_inf_or_nan(int len, char *str, t_format *f)
{
	f->len = len;
	if (!(f->str = (char*)malloc(sizeof(char) * (f->len + 1))))
		return (-1);
	f->str[f->len] = '\0';
	pft_strncpy(f->str, str, f->len);
	return (1);
}

int		check_int_and_nan(t_fl_itoa *a, t_format *f)
{
	f->len = 3;
	if (a->arg != a->arg)
		return (set_inf_or_nan(3, "nan", f));
	if (a->exp == 1024 && a->mant == 0)
	{
		if (a->sign)
			return (set_inf_or_nan(4, "-inf", f));
		else if (!f->flags[4])
		{
			if (!f->flags[0])
				return (set_inf_or_nan(3, "inf", f));
			else
				return (set_inf_or_nan(4, " inf", f));
		}
		else
			return (set_inf_or_nan(4, "+inf", f));
	}
	return (0);
}

void	get_double_rep(t_fl_itoa *a)
{
	double	n_cpy;
	unsigned char		*sign;
	unsigned short		*exp;
	unsigned long long	*mant;
	//unsigned long long	mant_copy;

	n_cpy = a->arg;
	sign = (unsigned char*)&n_cpy;
	sign += 7;
	a->sign = *sign;
	a->sign >>= 7;
	n_cpy = a->arg;
	exp = (unsigned short*)&n_cpy;
	exp += 3;
	*exp = *exp << 1;
	*exp = *exp >> 5;
	a->exp = *exp;
	a->exp -= 1023;
	n_cpy = a->arg;
	mant = (unsigned long long*)&n_cpy;
	a->mant = *mant;
	a->mant <<= 12;
	a->mant >>= 12;
	// a->mant += 4503599627370496;
	// ft_printf("%llu\n", a->mant);
	// *exp = 1023;
	// ft_printf("%llu\n", a->mant);
	// print_bits(8, &a->mant, 1);
	// mant_copy = a->mant;
	// a->mant >>= (52 - a->exp);
	// mant_copy <<= (12 + a->exp);
	// mant_copy >>= (12 + a->exp);
	// ft_printf("%llu\n", a->mant);
	// print_bits(8, &a->mant, 1);
	// ft_printf("%llu\n", mant_copy);
	// print_bits(8, &mant_copy, 1);
	// printf("%f", a->exp);
}
