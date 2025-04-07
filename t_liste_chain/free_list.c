#include "strct.h"

void	free_list(t_list *head)
{
	t_list	*current = head;
	t_list	*next;

	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	printf("NULL\n");
}