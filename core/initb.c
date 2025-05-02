/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:02:33 by saciurus          #+#    #+#             */
/*   Updated: 2025/05/02 13:10:32 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	set_target_b(t_list *a, t_list *b)
{
	t_list	*current_a;
	t_list	*target_node;
	long	best_m_i;

	while (b)
	{
		best_m_i = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value && current_a->value < best_m_i)
			{
				best_m_i = current_a->value;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (best_m_i == LONG_MAX)
			b->target_node = find_min(a);
		else
			b->target_node = target_node;
		b = b->next;
	}
}

void	init_nodes_b(t_list *a, t_list *b)
{
	current_index(a);
	current_index(b);
	set_target_b(a, b);
}
