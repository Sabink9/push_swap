#include "../push_swap.h"

void	reverse_rotate(t_list **x_stack)
{
	t_list	*current;
	t_list	*previous;
	t_list	*last;

	current = *x_stack;
	previous = NULL;
	if (*x_stack == NULL || (*x_stack)->next == NULL)
		return ;
	while (current->next != NULL)
	{
		previous = current;
		current = current->next;
	}
	last = current;
	previous->next = NULL;
	last->next = *x_stack;
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