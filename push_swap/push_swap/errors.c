#include "../push_swap.h"

int     error_syntax(char *s)
{
    if (!(*s == '+' || *s == '-' || ft_isdigit(*s)))
        return (1);
    if ((*s == '+' || *s == '-') && !ft_isdigit(s[1]))
        return (1);
    while (*++s)
        if (!ft_isdigit(*s))
            return (1);
    return (0);
}

int     error_duplicate(t_list *a, int n)
{
    if (!a)
        return (0);
    while (a)
    {
        if (a->value == n)
            return (1);
        a = a->next;
    }
    return (0);
}

void	free_stack(t_list **stack)
{
	t_list	*tmp;
	t_list	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void    free_errors(t_list **a)
{
    free_stack(a);
    ft_putstr("Error\n");
    exit(1);
}