/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:59:56 by saciurus          #+#    #+#             */
/*   Updated: 2025/04/12 18:59:57 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(char *str)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * signe);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	higher_nbr(t_list *a)
{
	int	value;

	value = a->value;
	while (a != NULL)
	{
		if (value < a->value)
			value = a->value;
		a = a->next;
	}
	return (value);
}

void	sort_in_a(t_list **a)
{
	t_list	*mid;

	mid = (*a)->next;
	if ((*a) == NULL || (*a)->next == NULL)
		return ;
	if ((*a)->value == higher_nbr(*a))
	{
		ra(a);
		if (mid->value > mid->next->value)
			sa(a);
	}
	else if ((*a)->value < mid->value)
	{
		if (mid->value > mid->next->value)
		{
			rra(a);
			sa(a);
		}
		else
			rra(a);
	}
	else
		sa(a);
}
