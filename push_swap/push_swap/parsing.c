#include "push_swap.h"

static void append_node(t_list **stack, int n)
{
    t_list *node = malloc(sizeof(*node));
    if (!node)
      return;
    node->nbr = n;
    node->cheapest = 0;
    node->next = NULL;
    if (!*stack)
    {
        node->prev = NULL;
        *stack = node;
    }
    else
    {
        t_list *last = *stack;
        while (last->next)
            last = last->next;
        last->next = node;
        node->prev = last;
    }
}

int     stack_len(t_list *stack)
{
    int i = 0;
    while (stack)
    {
        stack = stack->next;
        i++;
    }
    return (i);
}

void    init_stack_a(t_list **a, char **argv)
{
    int i = 0;
    while (argv[i])
    {
        if (error_syntax(argv[i]))
            free_errors(a);
        long n = ft_atol(argv[i]);
        if (n > 2147483647 || n < -2147483648)
            free_errors(a);
        if (error_duplicate(*a, (int)n))
            free_errors(a);
        append_node(a, (int)n);
        i++;
    }
}