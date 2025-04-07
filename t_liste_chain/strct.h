#ifndef STRCT_H
#define STRCT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	int		value;
	struct s_list	*next;
} t_list;

t_list	*create_node(int value);
void	append_node(t_list **head, int value);
void	print_list(t_list *head);
void	free_list(t_list *head);
void	remove_value(t_list **head, int value);
void	prepend_node(t_list **head, int value);
int	list_size(t_list *head);
void	reverse_list(t_list **head);

#endif