#include "push_swap.h"

void	sa(t_list **a)
{
	swap(a);
	ft_putstr("sa\n");
}

void	sb(t_list **b)
{
	swap(b);
	ft_putstr("sb\n");
}

void	ss(t_list **a, t_list **b)
{
	swap(a);
	swap(b);
	ft_putstr("ss\n");
}

void	pa(t_list **a, t_list **b)
{
	push(b, a);
	ft_putstr("pa\n");
}

void	pb(t_list **a, t_list **b)
{
	push(a, b);
	ft_putstr("pb\n");
}

void	ra(t_list **a)
{
	rotate(a);
	ft_putstr("ra\n");
}
void	rra(t_list **a)
{
	reverse_rotate(a);
	ft_putstr("rra\n");
}

void	rb(t_list **b)
{
	rotate(b);
	ft_putstr("rb\n");
}
void	rrb(t_list **b)
{
	reverse_rotate(b);
	ft_putstr("rrb\n");
}

void	rr(t_list **a, t_list **b)
{
	rotate(a);
	rotate(b);
	ft_putstr("rr\n");
}

void	rrr(t_list **a, t_list **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_putstr("rrr\n");
}