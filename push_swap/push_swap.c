#include "push_swap.h"

void push_swap(t_list **a)
{
    t_list *b = NULL;

    if (!stack_sorted(*a))
    {
        if (stack_len(*a) == 2)
            sa(a);
        else if (stack_len(*a) == 3)
            sort_three(a);
        else
            sort_stacks(a, &b);
    }
    print_list(*a);
    free_stack(a);
}

int main(int argc, char **argv)
{
    t_list *a = NULL;

    if (argc < 2 || (argc == 2 && !argv[1][0]))
        return (1);
    if (argc == 2)
        argv = split(argv[1], ' ');
    init_stack_a(&a, argv + 1);
    push_swap(&a);
    return (0);
}
