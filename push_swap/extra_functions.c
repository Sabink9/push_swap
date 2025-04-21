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

void    sort_three(t_list **a)
{
    if ((*a)->value > (*a)->next->value)
        sa(a);
    if ((*a)->next->value > (*a)->next->next->value)
        rra(a);
    if ((*a)->value > (*a)->next->value)
        sa(a);
}
