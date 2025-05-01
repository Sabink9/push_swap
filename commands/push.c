#include "../push_swap.h"

static void	push(t_list **dst, t_list **src)
{
	t_list	*push_node;

	if (!*src)
		return ;
	push_node = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	push_node->prev = NULL;
	if (!*dst)
	{
		*dst = push_node;
		push_node->next = NULL;
	}
	else
	{
		push_node->next = *dst;
		push_node->next->prev = push_node;
		*dst = push_node;
	}
}

void	pa(t_list **a, t_list **b, int print)
{
	push(a, b);
	if (!print)
		ft_putstr("pa\n");
}

void	pb(t_list **b, t_list **a, int print)
{
	push(b, a);
	if (!print)
		ft_putstr("pb\n");
}
