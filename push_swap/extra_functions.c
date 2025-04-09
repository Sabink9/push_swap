#include "push_swap.h"

void	ft_putstr(char *str)
{
	int i;
    
    i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_lstsize(t_list *lst)
{
	int size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return size;
}

int	get_max(t_list *a)
{
	int max = a->value;
	while (a)
	{
		if (a->value > max)
			max = a->value;
		a = a->next;
	}
	return max;
}

void	radix_sort(t_list **a, t_list **b)
{
	if (!*a)
		return ;
	int max_num = get_max(*a);
	int max_bits = 0;
	// Calcul du nombre de bits nécessaires
	while ((max_num >> max_bits) != 0)
		max_bits++;
	int bit = 0;
	while (bit < max_bits)
	{
		int i = 0;
		int size = ft_lstsize(*a);

		while (i < size)
		{
			int num = (*a)->value;
			if ((num >> bit) & 1)
				ra(a);
			else
				pb(a, b);
			i++;
		}
		// Tout ramener de B vers A (pa)
		while (*b)
			pa(a, b);
		bit++; // Passer au bit suivant
	}
}