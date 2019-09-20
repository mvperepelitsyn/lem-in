/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fnctns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:09:27 by uhand             #+#    #+#             */
/*   Updated: 2019/04/28 15:21:01 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		free_str(t_format *f)
{
	if (f->str != NULL)
		free(f->str);
	return (0);
}

int		free_buf(t_printf *p)
{
	if (p->str != NULL)
		free(p->str);
	return (-1);
}

void	tformat_init(t_format *f, t_printf *p)
{
	int		i;

	f->width = -1;
	f->precision = -1;
	f->type = -1;
	i = -1;
	while (++i < 5)
		f->flags[i] = 0;
	f->length[0] = 0;
	f->length[1] = 0;
	f->len = 0;
	f->str = NULL;
	f->start = -1;
	p->f_start = &f->start;
}

void	tprintf_init(t_printf *p)
{
	p->start = 0;
	p->i = 0;
	p->len = 0;
	p->str = NULL;
	p->method_arr[0] = (t_method) & format_c;
	p->method_arr[1] = (t_method) & format_s;
	p->method_arr[2] = (t_method) & format_p;
	p->method_arr[3] = (t_method) & format_f;
	p->method_arr[4] = (t_method) & format_d;
	p->method_arr[5] = (t_method) & format_oux;
	p->method_arr[6] = (t_method) & format_oux;
	p->method_arr[7] = (t_method) & format_oux;
	p->method_arr[8] = (t_method) & format_oux;
	p->method_arr[9] = (t_method) & format_c;
}

void	set_type(char c, t_format *f)
{
	if (c == 'c' || c == 'C')
		f->type = 0;
	else if (c == 's' || c == 'S')
		f->type = 1;
	else if (c == 'p')
		f->type = 2;
	else if (c == 'f' || c == 'F')
		f->type = 3;
	else if (c == 'd' || c == 'D')
		f->type = 4;
	else if (c == 'i')
		f->type = 4;
	else if (c == 'o' || c == 'O')
		f->type = 5;
	else if (c == 'u' || c == 'U')
		f->type = 6;
	else if (c == 'x')
		f->type = 7;
	else if (c == 'X')
		f->type = 8;
	else if (c == '%')
		f->type = 9;
}
