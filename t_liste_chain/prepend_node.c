#include "strct.h"

void	prepend_node(t_list **head, int value)
{
	t_list	*new_node = create_node(value);

	new_node->next = *head;
	*head = new_node;
}