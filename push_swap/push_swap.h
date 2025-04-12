/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:40 by saciurus          #+#    #+#             */
/*   Updated: 2025/04/12 18:36:24 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	struct s_list	*next;
	int				value;
}					t_list;

void	swap(t_list **head);
void	push(t_list **src, t_list **dest);
void	rotate(t_list **x_stack);
void	reverse_rotate(t_list **x_stack);
void	sa(t_list **a);
void	sb(t_list **b);
void	ss(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	pb(t_list **a, t_list **b);
void	ra(t_list **a);
void	rb(t_list **b);
void	rr(t_list **a, t_list **b);
void	rra(t_list **a);
void	rrb(t_list **b);
void	rrr(t_list **a, t_list **b);
void	insert_into_a(t_list **a, int argc, char **argv);
void	push_swap(t_list **a);
void	print_list(t_list *a);
void	ft_putstr(char *str);
void	sort_in_a(t_list **a);
int		ft_atoi(char *str);
int		higher_nbr(t_list *a);
int		has_duplicate(t_list *a, int value);
int		is_valid_integer(const char *str);
int		ft_lstsize(t_list *lst);

#endif