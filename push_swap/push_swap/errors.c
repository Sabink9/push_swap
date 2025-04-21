#include "push_swap.h"

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
    while (a)
    {
        if (a->nbr == n)
            return (1);
        a = a->next;
    }
    return (0);
}

void    free_stack(t_list **stack)
{
    t_list *cur;
    t_list *tmp;

    if (!stack || !*stack)
        return;
    cur = *stack;
    while (cur)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    *stack = NULL;
}

void    free_errors(t_list **a)
{
    free_stack(a);
    ft_putstr("Error\n");
    exit(1);
}