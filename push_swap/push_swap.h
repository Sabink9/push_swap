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
    int             nbr;
    int             index;
    int             push_cost;
    int             above_median;
    int             cheapest;
    struct s_list   *target_node;
    struct s_list   *next;
    struct s_list   *prev;
}  					t_list;

//commands
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

//error
int     error_syntax(char *s);
int     error_duplicate(t_list *a, int n);
void    free_stack(t_list **stack);
void    free_errors(t_list **a);

//split
char    **split(char *s, char c);
void    init_stack_a(t_list **a, char **argv);
void    append_node(t_list **stack, int n);

//utils
int     stack_len(t_list *stack);
int     stack_sorted(t_list *stack);
t_list  *find_last(t_list *stack);
t_list  *find_min(t_list *stack);
t_list  *find_max(t_list *stack);

//cost
void    current_index(t_list *stack);
void    init_nodes_a(t_list *a, t_list *b);
void    init_nodes_b(t_list *a, t_list *b);
void    set_target_a(t_list *a, t_list *b);
void    cost_analysis_a(t_list *a, t_list *b);
void    set_cheapest(t_list *stack);

//algorithms
void    sort_three(t_list **a);
void    sort_stacks(t_list **a, t_list **b);
void    print_list(t_list *a);

//aff
void    ft_putstr(char *str);
void    ft_putchar(char c);
void    ft_putnbr(int n);
int     ft_isdigit(int c);
static long ft_atol(const char *s);

#endif