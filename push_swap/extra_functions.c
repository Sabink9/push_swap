#include "push_swap.h"

int	ft_atoi(char *str)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * signe);
}

void	ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
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
		while (*b)
			pa(a, b);
		bit++;
	}
}

// void	insert_sort(t_list **a, t_list **b)
// {
// 	t_list *head = *a;
// }