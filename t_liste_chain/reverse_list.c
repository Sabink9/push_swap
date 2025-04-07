#include "strct.h"

void	reverse_list(t_list **head)
{
	t_list	*current = *head;
	t_list	*next = NULL;
	t_list	*previous = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*head = previous;
}