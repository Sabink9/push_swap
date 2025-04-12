/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:59:01 by saciurus          #+#    #+#             */
/*   Updated: 2025/04/12 18:59:02 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	rotate(t_list **x_stack)
{
	t_list	*first;
	t_list	*last;

	if (*x_stack == NULL || (*x_stack)->next == NULL)
		return ;
	first = *x_stack;
	last = *x_stack;
	while (last->next != NULL)
		last = last->next;
	*x_stack = first->next;
	last->next = first;
	first->next = NULL;
}

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
