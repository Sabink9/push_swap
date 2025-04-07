#include "strct.h"

void	append_node(t_list **head, int value)
{
	t_list	*current = *head;
	t_list	*new_node = create_node(value);
	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
}