#include "strct.h"

void	remove_value(t_list **head, int value)
{
	t_list	*current = *head;
	t_list	*next;
	t_list	*previous = NULL;

	if (*head == NULL)
		return ;
	if (current->value == value)
	{
		*head = current->next;
		free(current);
		return ;
	}
	while (current != NULL)
	{
		next = current->next;
		if (current->value == value)
		{
			previous->next = next;
			free(current);
			return ;
		}
		previous = current;
		current = next;	
	}
	printf("Valeur non trouve\n");
}

