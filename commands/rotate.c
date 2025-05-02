/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:02:16 by saciurus          #+#    #+#             */
/*   Updated: 2025/05/02 13:02:17 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rotate(t_list **stack)
{
	t_list	*last_node;

	if (!*stack || !(*stack)->next)
		return ;
	last_node = find_last(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}

void	ra(t_list **a, int print)
{
	rotate(a);
	if (!print)
		ft_putstr("ra\n");
}

void	rb(t_list **b, int print)
{
	rotate(b);
	if (!print)
		ft_putstr("rb\n");
}

void	rr(t_list **a, t_list **b, int print)
{
	rotate(a);
	rotate(b);
	if (!print)
		ft_putstr("rr\n");
}
