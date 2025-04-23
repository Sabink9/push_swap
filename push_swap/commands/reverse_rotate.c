#include "../push_swap.h"

void	reverse_rotate(t_list **x_stack)
{
	t_list	*last;

	if (!*x_stack || !(*x_stack)->next)
		return ;
	last = find_last(*x_stack);
	last->prev->next = NULL;
	last->prev = NULL;
	last->next = *x_stack;
	(*x_stack)->prev = last;
	*x_stack = last;
}


void	rra(t_list **a)
{
	reverse_rotate(a);
	ft_putstr("rra\n");
}

void	rrb(t_list **b)
{
	reverse_rotate(b);
	ft_putstr("rrb\n");
}

void	rrr(t_list **a, t_list **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_putstr("rrr\n");
}