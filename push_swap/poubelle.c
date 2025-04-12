// int	get_max(t_list *a)
// {
// 	int max = a->value;
// 	while (a)
// 	{
// 		if (a->value > max)
// 			max = a->value;
// 		a = a->next;
// 	}
// 	return max;
// }

// void	radix_sort(t_list **a, t_list **b)
// {
// 	if (!*a)
// 		return ;

// 	int max_num = get_max(*a);
// 	int max_bits = 0;

// 	while ((max_num >> max_bits) != 0)
// 		max_bits++;

// 	int bit = 0;
// 	while (bit < max_bits)
// 	{
// 		int i = 0;
// 		int size = ft_lstsize(*a);

// 		while (i < size)
// 		{
// 			int num = (*a)->value;
// 			if ((num >> bit) & 1)
// 				ra(a);
// 			else
// 				pb(a, b);
// 			i++;
// 		}
// 		while (*b)
// 			pa(a, b);
// 		bit++;
// 	}
// }