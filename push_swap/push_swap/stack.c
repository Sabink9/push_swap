#include "../push_swap.h"

static long ft_atoi(const char *s)
{
    long    res;
    int     sign;

    res = 0;
    sign = 1;
    while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
        s++;
    if (*s == '-' || *s == '+')
    {
        if (*s == '-')
            sign = -1;
        s++;
    }
    while (ft_isdigit(*s))
        res = res * 10 + (*s++ - '0');
    return (res * sign);
}

static void	append_node(t_list **stack, int n)
{
	t_list	*node;
	t_list	*last;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node->value = n;
	node->next = NULL;
	if (!*stack)
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last = find_last(*stack);
		last->next = node;
		node->prev = last;
	}
}

void	init_stack_a(t_list **a, char **argv)
{
	long	n;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			free_errors(a);
		n = ft_atoi(argv[i]);
		if (n > INT_MAX || n < INT_MIN)
			free_errors(a);
		if (error_duplicate(*a, (int)n))
			free_errors(a);
		append_node(a, (int)n);
		i++;
	}
}

t_list	*get_cheapest(t_list *stack)
{
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

void	prep_for_push(t_list **stack, t_list *top, char name)
{
	while (*stack != top)
	{
		if (name == 'a')
		{
			if (top->above_median)
				ra(stack);
			else
				rra(stack);
		}
		else if (name == 'b')
		{
			if (top->above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}