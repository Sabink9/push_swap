#include "push_swap.h"

int	*list_to_array(t_list *a, int size)
{
	int	*array;
	int	i;

	array = (int *)malloc(sizeof(int) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (a != NULL)
	{
		array[i] = a->value;
		a = a->next;
		i++;
	}
	return (array);
}

