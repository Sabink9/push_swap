#include "../push_swap.h"

void	rotate_both(t_list **a, t_list **b, t_list *cheapest_node)
{
	while (*b != cheapest_node->target_node && *a != cheapest_node)
		rr(a, b, 0);
	current_index(*a);
	current_index(*b);
}

void	rev_rotate_both(t_list **a, t_list **b, t_list *cheapest_node)
{
	while (*b != cheapest_node->target_node && *a != cheapest_node)
		rrr(a, b, 0);
	current_index(*a);
	current_index(*b);
}
