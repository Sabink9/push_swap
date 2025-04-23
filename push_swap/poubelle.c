#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	int				nbr;
	int				index;
	int				push_cost;
	int				above_median;
	int				cheapest;
	struct s_list	*target_node;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

int				error_syntax(char *str_n);
int				error_duplicate(t_list *a, int n);
void			free_stack(t_list **stack);
void			free_errors(t_list **a);
void			init_stack_a(t_list **a, char **argv);
char			**split(char *s, char c);
void			init_nodes_a(t_list *a, t_list *b);
void			init_nodes_b(t_list *a, t_list *b);
void			current_index(t_list *stack);
void			set_cheapest(t_list *stack);
t_list			*get_cheapest(t_list *stack);
void			prep_for_push(t_list **s, t_list *n, char c);
int				stack_len(t_list *stack);
t_list			*find_last(t_list *stack);
int				stack_sorted(t_list *stack);
t_list			*find_min(t_list *stack);
t_list			*find_max(t_list *stack);
void			sa(t_list **a, int print);
void			sb(t_list **b, int print);
void			ss(t_list **a, t_list **b, int print);
void			ra(t_list **a, int print);
void			rb(t_list **b, int print);
void			rr(t_list **a, t_list **b, int print);
void			rra(t_list **a, int print);
void			rrb(t_list **b, int print);
void			rrr(t_list **a, t_list **b, int print);
void			pa(t_list **a, t_list **b, int print);
void			pb(t_list **b, t_list **a, int print);
void			sort_three(t_list **a);
void			sort_stacks(t_list **a, t_list **b);

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
		ft_putchar(*s++);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int	error_syntax(char *str_n)
{
	if (!(*str_n == '+'
			|| *str_n == '-'
			|| (*str_n >= '0' && *str_n <= '9')))
		return (1);
	if ((*str_n == '+'
			|| *str_n == '-')
		&& !(str_n[1] >= '0' && str_n[1] <= '9'))
		return (1);
	while (*++str_n)
	{
		if (!(*str_n >= '0' && *str_n <= '9'))
			return (1);
	}
	return (0);
}

int	error_duplicate(t_list *a, int n)
{
	if (!a)
		return (0);
	while (a)
	{
		if (a->nbr == n)
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
		if (i <= median)
			stack->above_median = 1;
		else
			stack->above_median = 0;
		stack = stack->next;
		++i;
	}
}

static void	set_target_a(t_list *a, t_list *b)
{
	t_list	*current_b;
	t_list	*target_node;
	long	best_match_index;

	while (a)
	{
		best_match_index = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->nbr < a->nbr && current_b->nbr > best_match_index)
			{
				best_match_index = current_b->nbr;
				target_node = current_b;
			}
			current_b = current_b->next;
		}
		if (best_match_index == LONG_MIN)
			a->target_node = find_max(b);
		else
			a->target_node = target_node;
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
		if (!(a->above_median))
			a->push_cost = len_a - (a->index);
		if (a->target_node->above_median)
			a->push_cost += a->target_node->index;
		else
			a->push_cost += len_b - (a->target_node->index);
		a = a->next;
	}
}

void	set_cheapest(t_list *stack)
{
	long	cheapest_value;
	t_list	*cheapest_node;

	if (!stack)
		return ;
	cheapest_value = LONG_MAX;
	while (stack)
	{
		if (stack->push_cost < cheapest_value)
		{
			cheapest_value = stack->push_cost;
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
	long	best_match_index;

	while (b)
	{
		best_match_index = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->nbr > b->nbr && current_a->nbr < best_match_index)
			{
				best_match_index = current_a->nbr;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (best_match_index == LONG_MAX)
			b->target_node = find_min(a);
		else
			b->target_node = target_node;
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
	int		count;
	int	inside_word;

	count = 0;
	while (*s)
	{
		inside_word = 0;
		while (*s == c)
			++s;
		while (*s != c && *s)
		{
			if (!inside_word)
			{
				++count;
				inside_word = 1;
			}
			++s;
		}
	}
	return (count);
}

static char	*get_next_word(char *s, char c)
{
	static int	cursor = 0;
	char		*next_word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (s[cursor] == c)
		++cursor;
	while (s[cursor + len] != c && s[cursor + len])
		++len;
	next_word = malloc((size_t)len + 1);
	if (!next_word)
		return (NULL);
	while (s[cursor] != c && s[cursor])
		next_word[i++] = s[cursor++];
	next_word[i] = '\0';
	return (next_word);
}

char	**split(char *s, char c)
{
	int		words_count;
	char	**result_array;
	int		i;

	i = 0;
	words_count = count_words(s, c);
	if (!words_count)
		exit(1);
	result_array = malloc(sizeof(char *) * (size_t)(words_count + 2));
	if (!result_array)
		return (NULL);
	while (words_count-- >= 0)
	{
		if (i == 0)
		{
			result_array[i] = malloc(1);
			if (!result_array[i])
				return (NULL);
			result_array[i++][0] = '\0';
			continue ;
		}
		result_array[i++] = get_next_word(s, c);
	}
	result_array[i] = NULL;
	return (result_array);
}

static long	ft_atol(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

static void	append_node(t_list **stack, int n)
{
	t_list	*node;
	t_list	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node->next = NULL;
	node->nbr = n;
	node->cheapest = 0;
	if (!(*stack))
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*stack);
		last_node->next = node;
		node->prev = last_node;
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
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

void	prep_for_push(t_list **stack, t_list *top_node, char stack_name)
{
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
				ra(stack, 0);
			else
				rra(stack, 0);
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
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
		stack = stack->next;
		count++;
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
		if (stack->nbr > stack->next->nbr)
			return (0);
		stack = stack->next;
	}
	return (1);
}

t_list	*find_min(t_list *stack)
{
	long	min;
	t_list	*min_node;

	if (!stack)
		return (NULL);
	min = LONG_MAX;
	while (stack)
	{
		if (stack->nbr < min)
		{
			min = stack->nbr;
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

	if (!stack)
		return (NULL);
	max = LONG_MIN;
	while (stack)
	{
		if (stack->nbr > max)
		{
			max = stack->nbr;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

static void	push(t_list **dst, t_list **src)
{
	t_list	*push_node;

	if (!*src)
		return ;
	push_node = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	push_node->prev = NULL;
	if (!*dst)
	{
		*dst = push_node;
		push_node->next = NULL;
	}
	else
	{
		push_node->next = *dst;
		push_node->next->prev = push_node;
		*dst = push_node;
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
	t_list	*last_node;

	if (!*stack || !(*stack)->next)
		return ;
	last_node = find_last(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
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
	tmp->prev = *head;
	(*head)->prev = NULL;
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
	t_list	*biggest_node;

	biggest_node = find_max(*a);
	if (biggest_node == *a)
		ra(a, 0);
	else if ((*a)->next == biggest_node)
		rra(a, 0);
	if ((*a)->nbr > (*a)->next->nbr)
		sa(a, 0);
}

static void	rotate_both(t_list **a, t_list **b, t_list *cheapest_node)
{
	while (*b != cheapest_node->target_node && *a != cheapest_node)
		rr(a, b, 0);
	current_index(*a);
	current_index(*b);
}

static void	rev_rotate_both(t_list **a, t_list **b, t_list *cheapest_node)
{
	while (*b != cheapest_node->target_node && *a != cheapest_node)
		rrr(a, b, 0);
	current_index(*a);
	current_index(*b);
}

static void	move_a_to_b(t_list **a, t_list **b)
{
	t_list	*cheapest_node;

	cheapest_node = get_cheapest(*a);
	if (cheapest_node->above_median && cheapest_node->target_node->above_median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median)
		&& !(cheapest_node->target_node->above_median))
		rev_rotate_both(a, b, cheapest_node);
	prep_for_push(a, cheapest_node, 'a');
	prep_for_push(b, cheapest_node->target_node, 'b');
	pb(b, a, 0);
}

static void	move_b_to_a(t_list **a, t_list **b)
{
	prep_for_push(a, (*b)->target_node, 'a');
	pa(a, b, 0);
}

static void	min_on_top(t_list **a)
{
	while ((*a)->nbr != find_min(*a)->nbr)
	{
		if (find_min(*a)->above_median)
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
		ft_putnbr(a->nbr);
		ft_putchar(' ');
		a = a->next;
	}
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = split(argv[1], ' ');
	init_stack_a(&a, argv + 1);
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