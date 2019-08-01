/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats_c_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:43:32 by uhand             #+#    #+#             */
/*   Updated: 2019/04/25 13:06:59 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_c(t_printf *p, t_format *f, va_list *ap)
{
	if (!(f->str = (char*)malloc(sizeof(char) * 2)))
		return (0);
	f->str[1] = '\0';
	if (f->type == 0)
		f->str[0] = (char)va_arg(*ap, int);
	else if (f->type == 9)
		f->str[0] = '%';
	f->len = 1;
	return (char_flags(p, f));
}

int		format_s(t_printf *p, t_format *f, va_list *ap)
{
	char	*arg;

	arg = va_arg(*ap, char*);
	if (arg == NULL)
	{
		arg = "(null)";
		f->len = 6;
	}
	else
		f->len = ft_strlen(arg);
	if (f->precision >= 0 && f->precision < f->len)
		f->len = f->precision;
	if (!(f->str = (char*)malloc(sizeof(char) * (f->len + 1))))
		return (0);
	f->str[f->len] = '\0';
	pft_strncpy(f->str, arg, f->len);
	return (char_flags(p, f));
}
