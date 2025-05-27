/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saciurus <saciurus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:40 by saciurus          #+#    #+#             */
/*   Updated: 2025/05/27 16:31:56 by saciurus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				value;
	int				index;
	int				push_cost;
	int				above_median;
	int				cheapest;
	struct s_list	*target_node;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

//commands

void				sa(t_list **a, int print);
void				sb(t_list **b, int print);
void				ss(t_list **a, t_list **b, int print);
void				ra(t_list **a, int print);
void				rb(t_list **b, int print);
void				rr(t_list **a, t_list **b, int print);
void				rra(t_list **a, int print);
void				rrb(t_list **b, int print);
void				rrr(t_list **a, t_list **b, int print);
void				pa(t_list **a, t_list **b, int print);
void				pb(t_list **b, t_list **a, int print);

//error
int					error_syntax(char *s);
int					error_duplicate(t_list *a, int n);
void				free_stack(t_list **stack);
void				free_errors(t_list **a);

//split
char				**split(char *s, char c);

//stack
void				init_stack_a(t_list **a, char **argv);
t_list				*get_cheapest(t_list *stack);
void				prep_for_push(t_list **stack, t_list *top, char name);

//move
void				rotate_both(t_list **a, t_list **b, t_list *cheapest_node);
void				rev_rotate_both(t_list **a, t_list **b,
						t_list *cheapest_node);

//utils
int					stack_len(t_list *stack);
int					stack_sorted(t_list *stack);
t_list				*find_last(t_list *stack);
t_list				*find_min(t_list *stack);
t_list				*find_max(t_list *stack);

//cost
void				current_index(t_list *stack);
void				init_nodes_a(t_list *a, t_list *b);
void				init_nodes_b(t_list *a, t_list *b);
void				set_cheapest(t_list *stack);

//algorithms
void				sort_three(t_list **a);
void				sort_stacks(t_list **a, t_list **b);

//aff
void				ft_putstr(char *str);
void				ft_putchar(char c);
void				ft_putnbr(int n);
int					ft_isdigit(int c);

void				push_swap(t_list **a);

#endif