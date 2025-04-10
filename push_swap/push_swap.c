#include "push_swap.h"

void	push_swap(t_list **a)
{
	t_list *b = NULL;

	if (*a == NULL || (*a)->next == NULL)
		return ;

	// Pour les petites piles (2-5 éléments), utiliser un tri spécifique
	if (ft_lstsize(*a) <= 5)
	{
		// Implémenter un tri simple pour petites piles
		// (ex: tri par sélection avec rotations)
	}
	else
	{
		radix_sort(a, &b);
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		write(2, "Error\n", 6);
		return 1;
	}
	t_list *a = NULL;

	int i = 1;
	while (i < argc)
	{
		if (!is_valid_integer(argv[i]))
		{
			write(2, "Error\n", 6);
			return 1;
		}
		i++;
	}
	insert_into_a(&a, argc, argv);
	// printf("Before: ");
	// print_list(a);
	push_swap(&a);
	// printf("After: ");
	// // print_list(a);
	// // print_list(b);
	return 0;
}
