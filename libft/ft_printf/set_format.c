/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:42:26 by uhand             #+#    #+#             */
/*   Updated: 2019/05/21 18:35:52 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ---------------------------- Flags parsing ---------------------------------|
*/

static void	check_flag(t_format *f, int i)
{
	if (!f->flags[i])
		f->flags[i]++;
}

void		set_flags(t_printf *p, const char *format, t_format *f)
{
	while (P == ' ' || P == '#' || P == '0' || P == '-' || P == '+')
	{
		if (P == ' ')
			check_flag(f, 0);
		else if (P == '#')
			check_flag(f, 1);
		else if (P == '0')
			check_flag(f, 2);
		else if (P == '-')
			check_flag(f, 3);
		else if (P == '+')
			check_flag(f, 4);
		p->i++;
	}
}

/*
** ---------------------- Width & precision parsing ---------------------------|
*/

static void	get_wnp(t_printf *p, const char *format, va_list *ap, t_format *f)
{
	if (P != '*')
	{
		f->width = ft_atoi(&P);
		while (P >= '0' && P <= '9')
			p->i++;
	}
	else
	{
		f->width = va_arg(*ap, int);
		if (f->width < 0)
		{
			f->width = -(f->width);
			check_flag(f, 3);
		}
		p->i++;
	}
}

void		set_wnp(t_printf *p, const char *format, t_format *f, va_list *ap)
{
	if (P != '.')
		get_wnp(p, format, ap, f);
	if (P != '.')
		return ;
	p->i++;
	if (!((P >= '0' && P <= '9') || P == '*'))
	{
		f->precision = 0;
		return ;
	}
	if (P != '*')
	{
		f->precision = ft_atoi(&P);
		while (P >= '0' && P <= '9')
			p->i++;
	}
	else
	{
		f->precision = va_arg(*ap, int);
		p->i++;
	}
}

/*
** ---------------------------- Length parsing --------------------------------|
*/

void		set_length(t_printf *p, const char *format, t_format *f)
{
	f->length[0] = P;
	if (P == 'l' || P == 'h')
		if (format[p->i] == format[p->i + 1])
		{
			f->length[1] = P;
			p->i++;
		}
	p->i++;
}
