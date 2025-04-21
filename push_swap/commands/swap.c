#include "push_swap.h"

void	swap(t_list **head)
{
	t_list	*first;
	t_list	*second;

	first = *head;
	second = first->next;
	if (*head == NULL || (*head)->next == NULL)
		return ;
	first->next = second->next;
	second->next = first;
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
