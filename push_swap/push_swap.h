#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct s_list
{
	int	value;
	struct	s_list	*next;
	
}	t_list;

void push(t_list **src, t_list **dest);
void rotate(t_list **x_stack);
void pa(t_list **a, t_list **b);
void pb(t_list **a, t_list **b);
void ra(t_list **a);
int ft_lstsize(t_list *lst);
int	get_max(t_list *a);
void radix_sort(t_list **a, t_list **b);
void insert_into_a(t_list **a, int argc, char **argv);
int has_duplicate(t_list *a, int value);
int is_valid_integer(const char *str);
void push_swap(t_list **a);
void	print_list(t_list *a);
void	ft_putstr(char *str);
int	ft_atoi(char *str);

#endif