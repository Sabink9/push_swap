#include "push_swap.h"

int stack_len(t_list *stack)
{
    int i;

    i = 0;
    while (stack)
    {
        stack = stack->next;
        i++;
    }
    return (i);
}

t_list *find_last(t_list *s)
{
    while (s && s->next)
        s = s->next;
    return (s);
}

int stack_sorted(t_list *s)
{
    while (s && s->next)
    {
        if (s->nbr > s->next->nbr)
            return (0);
        s = s->next;
    }
    return (1);
}

t_list *find_min(t_list *s)
{
    long    min;
    t_list  *m;

    if (!s)
        return (NULL);
    min = LONG_MAX;
    while (s)
    {
        if (s->nbr < min)
        {
            min = s->nbr;
            m = s;
        }
        s = s->next;
    }
    return (m);
}

t_list *find_max(t_list *s)
{
    long    max;
    t_list  *m;

    if (!s)
        return (NULL);
    max = LONG_MIN;
    while (s)
    {
        if (s->nbr > max)
        {
            max = s->nbr;
            m = s;
        }
        s = s->next;
    }
    return (m);
}