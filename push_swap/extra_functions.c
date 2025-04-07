#include "push_swap.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

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