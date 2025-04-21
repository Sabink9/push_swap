/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:56:08 by saciurus          #+#    #+#             */
/*   Updated: 2025/04/12 18:57:03 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_duplicate(t_list *a, int value)
{
	while (a != NULL)
	{
		if (a->value == value)
			return (1);
		a = a->next;
	}
	return (0);
}

void	insert_into_a(t_list **a, int argc, char **argv)
{
	int		i;
	int		value;
	t_list	*new_node;

	i = argc - 1;
	while (i >= 1)
	{
		value = ft_atoi(argv[i]);
		if (has_duplicate(*a, value))
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		new_node = malloc(sizeof(t_list));
		new_node->value = value;
		new_node->next = *a;
		*a = new_node;
		i--;
	}
}

int	is_valid_integer(const char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	print_list(t_list *a)
{
	while (a)
	{
		printf("%d ", a->value);
		a = a->next;
	}
	printf("\n");
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
int find_min(t_list *stack)
{
    int min;

    min = stack->value;
    while (stack)
    {
        if (stack->value < min)
            min = stack->value;
        stack = stack->next;
    }
    return (min);
}
