#include "push_swap.h"

int	get_max(t_list *a)
{
	int max = a->value;
	while (a)
	{
		if (a->value > max)
			max = a->value;
		a = a->next;
	}
	return max;
}

void	radix_sort(t_list **a, t_list **b)
{
	if (!*a)
		return ;

	int max_num = get_max(*a);
	int max_bits = 0;

	// Calcul du nombre de bits nécessaires
	while ((max_num >> max_bits) != 0)
		max_bits++;

	int bit = 0;
	while (bit < max_bits)
	{
		int i = 0;
		int size = ft_lstsize(*a);

		while (i < size)
		{
			int num = (*a)->value;
			if ((num >> bit) & 1)
				ra(a);
			else
				pb(a, b);
			i++;
		}

		// Tout ramener de B vers A (pa)
		while (*b)
			pa(a, b);
		bit++; // Passer au bit suivant
	}
}

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
		radix_sort(a, &b);
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