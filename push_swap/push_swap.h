#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>

typedef	struct s_list
{
	int	value;
	struct	s_list	*next;
	
}	t_list;

void	swap(t_list **head);
void	push(t_list **src, t_list **dest);
void	rotate(t_list	**x_stack);
void	reverse_rotate(t_list **x_stack);
void	ft_putstr(char *str);
int	list_size(t_list *head);

#endif