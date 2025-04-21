#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_list
{
	int				value;
	int				index;
	int				push_cost;
	int				above_median;
	int				cheapest;
	struct s_list	*target_node;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

int	error_syntax(char *str_n);
int	error_duplicate(t_list *a, int n);
void	free_stack(t_list **stack);
void	free_errors(t_list **a);
void	init_stack_a(t_list **a, char **argv);
char	**split(char *s, char c);
void	init_nodes_a(t_list *a, t_list *b);
void	init_nodes_b(t_list *a, t_list *b);
void	current_index(t_list *stack);
void	set_cheapest(t_list *stack);
t_list	*get_cheapest(t_list *stack);
void	prep_for_push(t_list **s, t_list *n, char c);
int	stack_len(t_list *stack);
t_list	*find_last(t_list *stack);
int	stack_sorted(t_list *stack);
t_list	*find_min(t_list *stack);
t_list	*find_max(t_list *stack);
void	sa(t_list **a, int print);
void	sb(t_list **b, int print);
void	ss(t_list **a, t_list **b, int print);
void	ra(t_list **a, int print);
void	rb(t_list **b, int print);
void	rr(t_list **a, t_list **b, int print);
void	rra(t_list **a, int print);
void	rrb(t_list **b, int print);
void	rrr(t_list **a, t_list **b, int print);
void	pa(t_list **a, t_list **b, int print);
void	pb(t_list **b, t_list **a, int print);
void	sort_three(t_list **a);
void	sort_stacks(t_list **a, t_list **b);

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	error_syntax(char *str_n)
{
	if (!(*str_n == '+' || *str_n == '-' || (*str_n >= '0' && *str_n <= '9')))
		return (1);
	if ((*str_n == '+' || *str_n == '-') && !(str_n[1] >= '0' && str_n[1] <= '9'))
		return (1);
	while (*++str_n)
		if (!ft_isdigit(*str_n))
			return (1);
	return (0);
}

int	error_duplicate(t_list *a, int n)
{
	if (!a)
		return (0);
	while (a)
	{
		if (a->value == n)
			return (1);
		a = a->next;
	}
	return (0);
}

void	free_stack(t_list **stack)
{
	t_list	*tmp;
	t_list	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void	free_errors(t_list **a)
{
	free_stack(a);
	ft_putstr("Error\n");
	exit(1);
}

void	current_index(t_list *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = stack_len(stack) / 2;
	while (stack)
	{
		stack->index = i;
		stack->above_median = i <= median;
		stack = stack->next;
		++i;
	}
}

static void	set_target_a(t_list *a, t_list *b)
{
	t_list	*current_b;
	t_list	*target_node;
	long	best_match;

	while (a)
	{
		best_match = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->value < a->value && current_b->value > best_match)
			{
				best_match = current_b->value;
				target_node = current_b;
			}
			current_b = current_b->next;
		}
		a->target_node = target_node;
		if (best_match == LONG_MIN)
			a->target_node = find_max(b);
		a = a->next;
	}
}

static void	cost_analysis_a(t_list *a, t_list *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a)
	{
		a->push_cost = a->index;
		if (!a->above_median)
			a->push_cost = len_a - a->index;
		if (a->target_node->above_median)
			a->push_cost += a->target_node->index;
		else
			a->push_cost += len_b - a->target_node->index;
		a = a->next;
	}
}

void	set_cheapest(t_list *stack)
{
	long		cheapest_val;
	t_list	*cheapest_node;

	if (!stack)
		return ;
	cheapest_val = LONG_MAX;
	while (stack)
	{
		if (stack->push_cost < cheapest_val)
		{
			cheapest_val = stack->push_cost;
			cheapest_node = stack;
		}
		stack = stack->next;
	}
	cheapest_node->cheapest = 1;
}

void	init_nodes_a(t_list *a, t_list *b)
{
	current_index(a);
	current_index(b);
	set_target_a(a, b);
	cost_analysis_a(a, b);
	set_cheapest(a);
}

static void	set_target_b(t_list *a, t_list *b)
{
	t_list	*current_a;
	t_list	*target_node;
	long	best_match;

	while (b)
	{
		best_match = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value && current_a->value < best_match)
			{
				best_match = current_a->value;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		b->target_node = target_node;
		if (best_match == LONG_MAX)
			b->target_node = find_min(a);
		b = b->next;
	}
}

void	init_nodes_b(t_list *a, t_list *b)
{
	current_index(a);
	current_index(b);
	set_target_b(a, b);
}

static int	count_words(char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_word(char *s, char c)
{
	static int	cursor;
	char		*word;
	int			len;
	int			i;

	len = 0;
	while (s[cursor] == c)
		cursor++;
	while (s[cursor + len] != c && s[cursor + len])
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (s[cursor] != c && s[cursor])
		word[i++] = s[cursor++];
	word[i] = '\0';
	return (word);
}

char	**split(char *s, char c)
{
	char	**result;
	int		words;
	int		i;

	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < words)
	{
		result[i] = get_next_word(s, c);
		if (!result[i])
			return (NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

static long	ft_atol(const char *s)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		res = res * 10 + (*s++ - '0');
	return (res * sign);
}

static void	append_node(t_list **stack, int n)
{
	t_list	*node;
	t_list	*last;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node->value = n;
	node->next = NULL;
	if (!*stack)
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last = find_last(*stack);
		last->next = node;
		node->prev = last;
	}
}

void	init_stack_a(t_list **a, char **argv)
{
	long	n;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			free_errors(a);
		n = ft_atol(argv[i]);
		if (n > INT_MAX || n < INT_MIN)
			free_errors(a);
		if (error_duplicate(*a, (int)n))
			free_errors(a);
		append_node(a, (int)n);
		i++;
	}
}

t_list	*get_cheapest(t_list *stack)
{
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

void	prep_for_push(t_list **stack, t_list *top, char name)
{
	while (*stack != top)
	{
		if (name == 'a')
		{
			if (top->above_median)
				ra(stack, 0);
			else
				rra(stack, 0);
		}
		else if (name == 'b')
		{
			if (top->above_median)
				rb(stack, 0);
			else
				rrb(stack, 0);
		}
	}
}

int	stack_len(t_list *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

t_list	*find_last(t_list *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

int	stack_sorted(t_list *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

t_list	*find_min(t_list *stack)
{
	long	min;
	t_list	*min_node;

	min = LONG_MAX;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

t_list	*find_max(t_list *stack)
{
	long	max;
	t_list	*max_node;

	max = LONG_MIN;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

static void	push(t_list **dst, t_list **src)
{
	t_list	*node;

	if (!*src)
		return ;
	node = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node->prev = NULL;
	if (!*dst)
		*dst = node;
	else
	{
		node->next = *dst;
		(*dst)->prev = node;
		*dst = node;
	}
}

void	pa(t_list **a, t_list **b, int print)
{
	push(a, b);
	if (!print)
		ft_putstr("pa\n");
}

void	pb(t_list **b, t_list **a, int print)
{
	push(b, a);
	if (!print)
		ft_putstr("pb\n");
}

static void	rev_rotate(t_list **stack)
{
	t_list	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = find_last(*stack);
	last->prev->next = NULL;
	last->next = *stack;
	last->prev = NULL;
	*stack = last;
	last->next->prev = last;
}

void	rra(t_list **a, int print)
{
	rev_rotate(a);
	if (!print)
		ft_putstr("rra\n");
}

void	rrb(t_list **b, int print)
{
	rev_rotate(b);
	if (!print)
		ft_putstr("rrb\n");
}

void	rrr(t_list **a, t_list **b, int print)
{
	rev_rotate(a);
	rev_rotate(b);
	if (!print)
		ft_putstr("rrr\n");
}

static void	rotate(t_list **stack)
{
	t_list	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = find_last(*stack);
	last->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last->next->prev = last;
	last->next->next = NULL;
}

void	ra(t_list **a, int print)
{
	rotate(a);
	if (!print)
		ft_putstr("ra\n");
}

void	rb(t_list **b, int print)
{
	rotate(b);
	if (!print)
		ft_putstr("rb\n");
}

void	rr(t_list **a, t_list **b, int print)
{
	rotate(a);
	rotate(b);
	if (!print)
		ft_putstr("rr\n");
}

static void	swap(t_list **head)
{
	t_list	*tmp;

	if (!*head || !(*head)->next)
		return ;
	tmp = *head;
	*head = (*head)->next;
	tmp->next = (*head)->next;
	(*head)->next = tmp;
	(*head)->prev = NULL;
	tmp->prev = *head;
	if (tmp->next)
		tmp->next->prev = tmp;
}

void	sa(t_list **a, int print)
{
	swap(a);
	if (!print)
		ft_putstr("sa\n");
}

void	sb(t_list **b, int print)
{
	swap(b);
	if (!print)
		ft_putstr("sb\n");
}

void	ss(t_list **a, t_list **b, int print)
{
	swap(a);
	swap(b);
	if (!print)
		ft_putstr("ss\n");
}

void	sort_three(t_list **a)
{
	t_list	*max;

	max = find_max(*a);
	if (max == *a)
		ra(a, 0);
	else if ((*a)->next == max)
		rra(a, 0);
	if ((*a)->value > (*a)->next->value)
		sa(a, 0);
}

static void	move_a_to_b(t_list **a, t_list **b)
{
	t_list	*cheapest;

	cheapest = get_cheapest(*a);
	if (cheapest->above_median && cheapest->target_node->above_median)
		while (*a != cheapest && *b != cheapest->target_node)
			rr(a, b, 0);
	else if (!cheapest->above_median && !cheapest->target_node->above_median)
		while (*a != cheapest && *b != cheapest->target_node)
			rrr(a, b, 0);
	prep_for_push(a, cheapest, 'a');
	prep_for_push(b, cheapest->target_node, 'b');
	pb(b, a, 0);
}

static void	move_b_to_a(t_list **a, t_list **b)
{
	prep_for_push(a, (*b)->target_node, 'a');
	pa(a, b, 0);
}

static void	min_on_top(t_list **a)
{
	t_list	*min;

	min = find_min(*a);
	while (*a != min)
	{
		if (min->above_median)
			ra(a, 0);
		else
			rra(a, 0);
	}
}

void	sort_stacks(t_list **a, t_list **b)
{
	int	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a, 0);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a, 0);
	while (len_a-- > 3 && !stack_sorted(*a))
	{
		init_nodes_a(*a, *b);
		move_a_to_b(a, b);
	}
	sort_three(a);
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
	current_index(*a);
	min_on_top(a);
}

void	print_list(t_list *a)
{
	while (a)
	{
		printf("%d ", a->value);
		a = a->next;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	if (argc == 2)
		argv = split(argv[1], ' ');
	init_stack_a(&a, argv + (argc == 2 ? 0 : 1));
	if (argc == 2)
		free(argv);
	if (!stack_sorted(a))
	{
		if (stack_len(a) == 2)
			sa(&a, 0);
		else if (stack_len(a) == 3)
			sort_three(&a);
		else
			sort_stacks(&a, &b);
	}
    print_list(a);
	free_stack(&a);
	return (0);
}