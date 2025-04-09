#include "push_swap.h"

void	pa(t_list **a, t_list **b)
{
	push(a, b);
	ft_putstr("pa\n");
}

void	pb(t_list **b, t_list **a)
{
	push(b, a);
	ft_putstr("pb\n");
}

void	ra(t_list **a)
{
	rotate(a);
	ft_putstr("ra\n");
}
