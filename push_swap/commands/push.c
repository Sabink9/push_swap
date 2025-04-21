#include "../push_swap.h"

void	push(t_list **src, t_list **dest)
{
	t_list	*temp;

	if (*src == NULL)
		return ;
	temp = *src;
	*src = (*src)->next;
	temp->next = *dest;
	*dest = temp;
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