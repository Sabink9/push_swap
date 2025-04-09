#include "push_swap.h"

// void	swap(t_list **head)
// {
// 	t_list	*first = *head;
// 	t_list	*second = first->next;

// 	if (*head == NULL || (*head)->next == NULL)
// 		return ;

// 	first->next = second->next;
// 	second->next = first;
// 	*head = second;
// }

void	push(t_list **src, t_list **dest)
{
	if (*src == NULL)
		return ;
	t_list *temp = *src;
	*src = (*src)->next;
	temp->next = *dest;
	*dest = temp;
}

void	rotate(t_list **x_stack)
{
	if (*x_stack == NULL || (*x_stack)->next == NULL)
		return ;
	t_list *first = *x_stack;
	t_list *last = *x_stack;
	while (last->next != NULL)
		last = last->next;
	*x_stack = first->next;
	last->next = first;
	first->next = NULL;
}

// void	reverse_rotate(t_list **x_stack)
// {
// 	t_list	*current = *x_stack;
// 	t_list	*previous = NULL;
// 	t_list	*last;

// 	if (*x_stack == NULL || (*x_stack)->next == NULL)
// 		return ;
// 	while(current->next != NULL)
// 	{
// 		previous = current;
// 		current = current->next;
// 	}		
// 	last = current;
// 	previous->next = NULL;
// 	last->next = *x_stack;
// 	*x_stack = last;
// }

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