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

	// Vérifier les doublons et la validité des entiers avant d'insérer dans la pile
	int i = 1;
	while (i < argc)
	{
		if (!is_valid_integer(argv[i])) // Vérifier si l'argument est un entier valide
		{
			write(2, "Error\n", 6); // Afficher l'erreur si un argument n'est pas valide
			return 1;
		}
		i++;
	}

	// Insérer les éléments dans la pile A
	insert_into_a(&a, argc, argv);

	printf("Before: ");
	print_list(a);

	push_swap(&a);

	printf("After: ");
	print_list(a);

	return 0;
}