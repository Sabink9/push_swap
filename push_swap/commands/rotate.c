#include "../push_swap.h"

void	rotate(t_list **x_stack)
{
	t_list	*first;
	t_list	*last;

	if (!*x_stack || !(*x_stack)->next)
		return ;
	first = *x_stack;
	last = find_last(*x_stack);
	*x_stack = first->next;
	(*x_stack)->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
}

void	ra(t_list **a)
{
	rotate(a);
	ft_putstr("ra\n");
}

void	rb(t_list **b)
{
	rotate(b);
	ft_putstr("rb\n");
}

void	rr(t_list **a, t_list **b)
{
	rotate(a);
	rotate(b);
	ft_putstr("rr\n");
}