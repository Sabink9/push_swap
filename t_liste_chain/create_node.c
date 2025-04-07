#include "strct.h"

t_list	*create_node(int value)
{
	t_list	*node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}