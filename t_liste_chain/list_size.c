#include "strct.h"

int	list_size(t_list *head)
{
	int	i = 0;

	t_list	*current = head;

	if (head == NULL)
		return (0);
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}