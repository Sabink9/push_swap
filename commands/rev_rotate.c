/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:02:13 by saciurus          #+#    #+#             */
/*   Updated: 2025/05/02 13:04:19 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rev_rotate(t_list **stack)
{
	t_list	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = find_last(*stack);
	last->prev->next = NULL;
	last->next = *stack;
	last->prev = NULL;
	*stack = last;
	last->next->prev = last;
}

void	rra(t_list **a, int print)
{
	rev_rotate(a);
	if (!print)
		ft_putstr("rra\n");
}

void	rrb(t_list **b, int print)
{
	rev_rotate(b);
	if (!print)
		ft_putstr("rrb\n");
}

void	rrr(t_list **a, t_list **b, int print)
{
	rev_rotate(a);
	rev_rotate(b);
	if (!print)
		ft_putstr("rrr\n");
}
