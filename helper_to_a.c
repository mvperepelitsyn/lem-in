/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:36:03 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/11 17:40:55 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
//
//int		imed(t_stack *stack, int med)
//{
//	int i;
//
//	i = 0;
//	while (++i <= stack->a_size)
//	{
//		if (stack->a_stack[i] <= med)
//			return (i);
//	}
//	return (0);
//}
//
//short	no_med(t_stack *stack, int med)
//{
//	int i;
//
//	i = stack->a_size;
//	while (i > 0)
//	{
//		if (stack->a_stack[i] <= med)
//			return (0);
//		i--;
//	}
//	return (1);
//}
//
//int		get_max(t_stack *stack)
//{
//	int i;
//	int max;
//
//	i = 0;
//	max = -2147483648;
//	while (++i <= stack->a_size)
//	{
//		if (stack->a_stack[i] > max)
//			max = stack->a_stack[i];
//	}
//	return (max);
//}
//
//int		give_next_min(t_stack *stack, int min)
//{
//	int i;
//	int	nxt;
//
//	i = stack->a_size;
//	nxt = get_max(stack);
//	while (i > 0)
//	{
//		if (stack->a_stack[i] > min && stack->a_stack[i] < nxt)
//			nxt = stack->a_stack[i];
//		i--;
//	}
//	return (nxt);
//}
//
//int		give_med(t_stack *stack)
//{
//	int med;
//	int cnt;
//
//	med = get_min(stack);
//	cnt = stack->a_size / 2;
//	while (cnt != 1)
//	{
//		med = give_next_min(stack, med);
//		cnt--;
//	}
//	return (med);
//}
