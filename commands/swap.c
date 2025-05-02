/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:02:19 by saciurus          #+#    #+#             */
/*   Updated: 2025/05/02 13:02:20 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	swap(t_list **head)
{
	t_list	*tmp;

	if (!*head || !(*head)->next)
		return ;
	tmp = *head;
	*head = (*head)->next;
	tmp->next = (*head)->next;
	(*head)->next = tmp;
	tmp->prev = *head;
	(*head)->prev = NULL;
	if (tmp->next)
		tmp->next->prev = tmp;
}

void	sa(t_list **a, int print)
{
	swap(a);
	if (!print)
		ft_putstr("sa\n");
}

void	sb(t_list **b, int print)
{
	swap(b);
	if (!print)
		ft_putstr("sb\n");
}

void	ss(t_list **a, t_list **b, int print)
{
	swap(a);
	swap(b);
	if (!print)
		ft_putstr("ss\n");
}
