/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:35:41 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/02 13:35:43 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_malloc_error(void)
{
	ft_putstr("Malloc didn't allocate the memory\n");
	exit (69);
}

short	no_med_b(t_stack *stack, int med)
{
	int i;

	i = stack->b_size;
	while (i > 0)
	{
		if (stack->b_stack[i] >= med)
			return (0);
		i--;
	}
	return (1);
}

int		get_min_b(t_stack *stack)
{
	int i;
	int min;

	i = 0;
	min = 2147483647;
	while (++i <= stack->b_size)
	{
		if (stack->b_stack[i] < min)
			min = stack->b_stack[i];
	}
	return (min);
}

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(69);
}

int		get_min(t_stack *stack)
{
	int i;
	int min;

	i = 0;
	min = 2147483647;
	while (++i <= stack->a_size)
	{
		if (stack->a_stack[i] < min)
			min = stack->a_stack[i];
	}
	return (min);
}

void	init_stack(t_stack *stack, int argc)
{
	stack->a_stack = (int *)malloc(sizeof(int) * argc);
	stack->b_stack = (int *)malloc(sizeof(int) * argc);
	stack->a_size = argc - 1;
	stack->b_size = 0;
}
