/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_to_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:36:15 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/02 13:36:17 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
//#include "push_swap.h"
//
//int		give_next_min_b(t_stack *stack, int min)
//{
//	int i;
//	int	nxt;
//
//	i = stack->b_size;
//	nxt = get_max_b(stack);
//	while (i > 0)
//	{
//		if (stack->b_stack[i] > min && stack->b_stack[i] < nxt)
//			nxt = stack->b_stack[i];
//		i--;
//	}
//	return (nxt);
//}
//
//int		give_med_b(t_stack *stack)
//{
//	int med;
//	int cnt;
//
//	med = get_min_b(stack);
//	cnt = stack->b_size / 2;
//	while (cnt != 1)
//	{
//		med = give_next_min_b(stack, med);
//		cnt--;
//	}
//	return (med);
//}
//
//int		get_imax_b(t_stack *stack)
//{
//	int i;
//	int max;
//	int imax;
//
//	i = 0;
//	imax = 0;
//	max = -2147483648;
//	while (++i <= stack->b_size)
//	{
//		if (stack->b_stack[i] > max)
//		{
//			max = stack->b_stack[i];
//			imax = i;
//		}
//	}
//	return (imax);
//}
//
//int		get_max_b(t_stack *stack)
//{
//	int i;
//	int max;
//
//	i = 0;
//	max = -2147483648;
//	while (++i <= stack->b_size)
//	{
//		if (stack->b_stack[i] > max)
//			max = stack->b_stack[i];
//	}
//	return (max);
//}
//
//int		imed_b(t_stack *stack, int med)
//{
//	int i;
//
//	i = 0;
//	while (++i <= stack->b_size)
//	{
//		if (stack->b_stack[i] <= med)
//			return (i);
//	}
//	return (0);
//}
