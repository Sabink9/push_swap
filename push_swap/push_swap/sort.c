#include "../push_swap.h"

void	sort_three(t_list **a)
{
	t_list	*max;

	max = find_max(*a);
	if (max == *a)
		ra(a);
	else if ((*a)->next == max)
		rra(a);
	if ((*a)->value > (*a)->next->value)
		sa(a);
}

static void	move_a_to_b(t_list **a, t_list **b)
{
	t_list	*cheapest;

	cheapest = get_cheapest(*a);
	if (cheapest->above_median && cheapest->target_node->above_median)
		while (*a != cheapest && *b != cheapest->target_node)
			rr(a, b);
	else if (!cheapest->above_median && !cheapest->target_node->above_median)
		while (*a != cheapest && *b != cheapest->target_node)
			rrr(a, b);
	prep_for_push(a, cheapest, 'a');
	prep_for_push(b, cheapest->target_node, 'b');
	pb(b, a);
}

static void	move_b_to_a(t_list **a, t_list **b)
{
	prep_for_push(a, (*b)->target_node, 'a');
	pa(a, b);
}

static void	min_on_top(t_list **a)
{
	t_list	*min;

	min = find_min(*a);
	while (*a != min)
	{
		if (min->above_median)
			ra(a);
		else
			rra(a);
	}
}

void	sort_stacks(t_list **a, t_list **b)
{
	int	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a);
	while (len_a-- > 3 && !stack_sorted(*a))
	{
		init_nodes_a(*a, *b);
		move_a_to_b(a, b);
	}
	sort_three(a);
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
	current_index(*a);
	min_on_top(a);
}