/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:02:39 by saciurus          #+#    #+#             */
/*   Updated: 2025/05/28 17:05:42 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

//#include <stdio.h>

void	push_swap(t_list **a)
{
	t_list	*b;
	int		len;

	b = NULL;
	if (stack_sorted(*a))
		return ;
	len = stack_len(*a);
	if (len == 2)
		sa(a, 0);
	else if (len == 3)
		sort_three(a);
	else
		sort_stacks(a, &b);
}

// void	print_stack(t_list *a)
// {
// 	while (a)
// 	{
// 		ft_printf("%d\n", a->value);
// 		a = a->next;
// 	}
// }

int	main(int argc, char **argv)
{
	t_list	*a;
	char	**split_argv;

	a = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	if (argc == 2)
	{
		split_argv = split(argv[1], ' ');
		if (!split_argv)
			return (1);
		if (init_stack_a(&a, split_argv))
		{
			free_split(split_argv);
			return (1);
		}
		free_split(split_argv);
	}
	else
		return (init_stack_a(&a, argv + 1) ? 1 : 0);
	push_swap(&a);
	free_stack(&a);
	return (0);
}
