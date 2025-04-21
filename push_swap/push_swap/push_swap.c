#include "../push_swap.h"

void	push_swap(t_list **a)
{
	t_list	*b;
	int		len;

	b = NULL;
	if (stack_sorted(*a))
		return ;
	len = stack_len(*a);
	if (len == 2)
		sa(a);
	else if (len == 3)
		sort_three(a);
	else
		sort_stacks(a, &b);
	free_stack(&b);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	char	**split_argv;

	a = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	if (argc == 2)
	{
		split_argv = split(argv[1], ' ');
		init_stack_a(&a, split_argv);
	}
	else
		init_stack_a(&a, argv + 1);
	push_swap(&a);
	free_stack(&a);
	return (0);
}