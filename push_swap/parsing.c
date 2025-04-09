#include "push_swap.h"

void	print_list(t_list *a)
{
	while (a)
	{
		printf("%d ", a->value);
		a = a->next;
	}
	printf("\n");
}

void	insert_into_a(t_list **a, int argc, char **argv)
{
	int i = 1;
	while (i < argc)
	{
		int value = atoi(argv[i]);

		// Vérifier les doublons avant d'insérer
		if (has_duplicate(*a, value))
		{
			write(2, "Error\n", 6);
			exit(1); // Terminer le programme en cas de doublon
		}

		// Créer le nouveau noeud
		t_list *new_node = malloc(sizeof(t_list));
		new_node->value = value;
		new_node->next = *a;
		*a = new_node;
		i++;
	}
}

int	has_duplicate(t_list *a, int value)
{
	while (a != NULL)
	{
		if (a->value == value)
			return (1);
		a = a->next;
	}
	return (0);
}

int	is_valid_integer(const char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}