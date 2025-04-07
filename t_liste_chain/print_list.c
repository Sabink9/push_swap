#include "strct.h"

void	print_list(t_list *head)
{
	t_list	*current = head;
	while (current != NULL)
	{
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}