#include "push_swap.h"

void    sort_three(t_list **a)
{
    if ((*a)->value > (*a)->next->value)
        sa(a);
    if ((*a)->next->value > (*a)->next->next->value)
        rra(a);
    if ((*a)->value > (*a)->next->value)
        sa(a);
}

void    final_rotate(t_list **a)
{
    int min;
    int pos;
    t_list *tmp;

    min = find_min(*a);
    pos = 0;
    tmp = *a;
    while (tmp->value != min && ++pos)
        tmp = tmp->next;
    if (pos > ft_lstsize(*a) / 2)
        while ((*a)->value != min)
            rra(a);
    else
        while ((*a)->value != min)
            ra(a);
}