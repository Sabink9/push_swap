#include "../push_swap.h"

void	swap(t_list **head)
{
	t_list	*first;
	t_list	*second;

	if (!*head || !(*head)->next)
		return ;
	first = *head;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*head = second;
}

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
