/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:13:27 by uhand             #+#    #+#             */
/*   Updated: 2019/04/28 14:59:40 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** -------------------------- Signed int formats ------------------------------|
*/

static long long	take_less(va_list *ap, int type)
{
	long long	arg;
	short int	arg_short;
	char		arg_char;

	if (type == 1)
	{
		arg_char = (char)va_arg(*ap, int);
		arg = (long long)arg_char;
	}
	else
	{
		arg_short = (short int)va_arg(*ap, int);
		arg = (long long)arg_short;
	}
	return (arg);
}

int					format_d(t_printf *p, t_format *f, va_list *ap)
{
	long long	arg;

	if (f->length[0] != 0 && (f->length[0] == 'l' || f->length[0] == 'h'))
	{
		if (f->length[0] == 'l')
		{
			if (f->length[1] == 'l')
				arg = va_arg(*ap, long long);
			else
				arg = (long long)va_arg(*ap, long int);
		}
		if (f->length[0] == 'h')
		{
			if (f->length[1] == 'h')
				arg = take_less(ap, 1);
			else
				arg = take_less(ap, 2);
		}
	}
	else
		arg = (long long)va_arg(*ap, int);
	if (!(f->str = pft_itoa(arg, f)))
		return (0);
	return (int_flags(p, f));
}

/*
** ------------------------- Unsigned int formats -----------------------------|
*/

static long long	take_less_unsigned(va_list *ap, int type)
{
	unsigned long long	arg;
	unsigned short int	arg_short;
	unsigned char		arg_char;

	if (type == 1)
	{
		arg_char = (unsigned char)va_arg(*ap, unsigned int);
		arg = (unsigned long long)arg_char;
	}
	else
	{
		arg_short = (unsigned short int)va_arg(*ap, unsigned int);
		arg = (unsigned long long)arg_short;
	}
	return (arg);
}

int					format_oux(t_printf *p, t_format *f, va_list *ap)
{
	unsigned long long	arg;

	if (f->length[0] != 0 && (f->length[0] == 'l' || f->length[0] == 'h'))
	{
		if (f->length[0] == 'l')
		{
			if (f->length[1] == 'l')
				arg = va_arg(*ap, unsigned long long);
			else
				arg = (unsigned long long)va_arg(*ap, unsigned long int);
		}
		if (f->length[0] == 'h')
		{
			if (f->length[1] == 'h')
				arg = take_less_unsigned(ap, 1);
			else
				arg = take_less_unsigned(ap, 2);
		}
	}
	else
		arg = (unsigned long long)va_arg(*ap, unsigned int);
	if (!(f->str = pft_unsigned_itoa(arg, f)))
		return (0);
	return (int_flags(p, f));
}

/*
** ---------------------------- Address format --------------------------------|
*/

int					format_p(t_printf *p, t_format *f, va_list *ap)
{
	unsigned long long	arg;

	arg = (unsigned long long)va_arg(*ap, void*);
	f->flags[1] = 1;
	f->flags[2] = 0;
	if (!(f->str = pft_unsigned_itoa(arg, f)))
		return (0);
	return (int_flags(p, f));
}
