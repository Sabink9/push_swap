#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_list
{
    int             nbr;
    int             index;
    int             push_cost;
    int             above_median;
    int             cheapest;
    struct s_list   *target_node;
    struct s_list   *next;
    struct s_list   *prev;
}   t_list;

/* ================== FONCTIONS UTILITAIRES ================== */

static void ft_putstr(char *s)
{
    int i = 0;
    while (s[i])
        write(1, &s[i++], 1);
}

static int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

static long ft_atol(const char *s)
{
    long res = 0;
    int sign = 1;

    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    if (*s == '-' || *s == '+')
        sign = 1 - 2 * (*(s++) == '-');
    while (ft_isdigit(*s))
        res = res * 10 + (*s++ - '0');
    return (res * sign);
}

/* ================== GESTION DE LA MÉMOIRE ================== */

static void free_stack(t_list **stack)
{
    t_list *tmp;
    t_list *current = *stack;

    while (current)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    *stack = NULL;
}

static void error_exit(t_list **a)
{
    free_stack(a);
    ft_putstr("Error\n");
    exit(1);
}

/* ================== OPÉRATIONS DE BASE ================== */

static void pa(t_list **a, t_list **b, int print)
{
    t_list *tmp = *b;
    if (!tmp) return;
    
    *b = (*b)->next;
    if (*b) (*b)->prev = NULL;
    tmp->next = *a;
    if (*a) (*a)->prev = tmp;
    *a = tmp;
    if (print) ft_putstr("pa\n");
}

static void pb(t_list **b, t_list **a, int print) { pa(a, b, 0); if (print) ft_putstr("pb\n"); }

static void sa(t_list **a, int print)
{
    if (!*a || !(*a)->next) return;
    
    t_list *first = *a;
    t_list *second = first->next;
    
    first->next = second->next;
    if (second->next) second->next->prev = first;
    second->prev = NULL;
    second->next = first;
    first->prev = second;
    *a = second;
    if (print) ft_putstr("sa\n");
}

static void sb(t_list **b, int print) { sa(b, print); if (print) ft_putstr("sb\n"); }
static void ss(t_list **a, t_list **b, int print) { sa(a, 0); sb(b, 0); if (print) ft_putstr("ss\n"); }

static void ra(t_list **a, int print)
{
    if (!*a || !(*a)->next) return;
    
    t_list *last = *a;
    while (last->next) last = last->next;
    
    last->next = *a;
    (*a)->prev = last;
    *a = (*a)->next;
    (*a)->prev->next = NULL;
    (*a)->prev = NULL;
    if (print) ft_putstr("ra\n");
}

static void rb(t_list **b, int print) { ra(b, print); if (print) ft_putstr("rb\n"); }
static void rr(t_list **a, t_list **b, int print) { ra(a, 0); ra(b, 0); if (print) ft_putstr("rr\n"); }

static void rra(t_list **a, int print)
{
    if (!*a || !(*a)->next) return;
    
    t_list *last = *a;
    while (last->next) last = last->next;
    
    last->prev->next = NULL;
    last->next = *a;
    last->prev = NULL;
    (*a)->prev = last;
    *a = last;
    if (print) ft_putstr("rra\n");
}

static void rrb(t_list **b, int print) { rra(b, print); if (print) ft_putstr("rrb\n"); }
static void rrr(t_list **a, t_list **b, int print) { rra(a, 0); rra(b, 0); if (print) ft_putstr("rrr\n"); }

/* ================== INITIALISATION STACK ================== */

static void append_node(t_list **stack, int n)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node) error_exit(stack);

    node->nbr = n;
    node->next = NULL;
    node->prev = NULL;
    node->cheapest = 0;
    node->push_cost = 0;
    node->above_median = 0;
    node->target_node = NULL;

    if (!*stack)
        *stack = node;
    else
    {
        t_list *last = *stack;
        while (last->next)
            last = last->next;
        last->next = node;
        node->prev = last;
    }
}

static char **split(char *s, char c)
{
    int count = 0;
    int len = 0;
    char **res;
    char *start;

    while (*s)
    {
        while (*s == c) s++;
        len = 0;
        start = s;
        while (*s && *s != c) { s++; len++; }
        if (len > 0) count++;
    }
    
    res = malloc(sizeof(char *) * (count + 1));
    s = start - len - (s - start);
    
    count = 0;
    while (*s)
    {
        while (*s == c) s++;
        if (!*s) break;
        start = s;
        while (*s && *s != c) s++;
        res[count] = malloc(s - start + 1);
        for (int i = 0; start < s; i++)
            res[count][i] = *start++;
        res[count++][s - start] = '\0';
    }
    res[count] = NULL;
    return res;
}

/* ================== FONCTIONS DE TRI ================== */

static t_list *find_min(t_list *stack)
{
    t_list *min = stack;
    while (stack)
    {
        if (stack->nbr < min->nbr)
            min = stack;
        stack = stack->next;
    }
    return min;
}

static t_list *find_max(t_list *stack)
{
    t_list *max = stack;
    while (stack)
    {
        if (stack->nbr > max->nbr)
            max = stack;
        stack = stack->next;
    }
    return max;
}

static void current_index(t_list *stack)
{
    int i = 0;
    int median = stack_len(stack) / 2;
    while (stack)
    {
        stack->index = i;
        stack->above_median = (i <= median);
        stack = stack->next;
        i++;
    }
}

static void set_target_a(t_list *a, t_list *b)
{
    t_list *current_b;
    t_list *target;
    long best_match;

    while (a)
    {
        best_match = LONG_MIN;
        current_b = b;
        while (current_b)
        {
            if (current_b->nbr < a->nbr && current_b->nbr > best_match)
            {
                best_match = current_b->nbr;
                target = current_b;
            }
            current_b = current_b->next;
        }
        a->target_node = (best_match == LONG_MIN) ? find_max(b) : target;
        a = a->next;
    }
}

static void cost_analysis_a(t_list *a, t_list *b)
{
    int len_a = stack_len(a);
    int len_b = stack_len(b);

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

static void set_cheapest(t_list *stack)
{
    long cheapest = LONG_MAX;
    t_list *cheapest_node = stack;

    while (stack)
    {
        if (stack->push_cost < cheapest)
        {
            cheapest = stack->push_cost;
            cheapest_node = stack;
        }
        stack = stack->next;
    }
    cheapest_node->cheapest = 1;
}

static void init_nodes_a(t_list *a, t_list *b)
{
    current_index(a);
    current_index(b);
    set_target_a(a, b);
    cost_analysis_a(a, b);
    set_cheapest(a);
}

static void prep_for_push(t_list **stack, t_list *top, char name)
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

static void move_a_to_b(t_list **a, t_list **b)
{
    t_list *cheapest = get_cheapest(*a);
    
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

static void sort_three(t_list **a)
{
    t_list *max = find_max(*a);
    
    if (max == *a)
        ra(a, 0);
    else if (max == (*a)->next)
        rra(a, 0);
    if ((*a)->nbr > (*a)->next->nbr)
        sa(a, 0);
}

static void sort_stacks(t_list **a, t_list **b)
{
    int len = stack_len(*a);
    
    pb(b, a, 0);
    pb(b, a, 0);
    while (stack_len(*a) > 3)
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

void push_swap(t_list **a)
{
    t_list *b = NULL;
    int len = stack_len(*a);
    
    if (len == 1) return;
    if (len == 2) sa(a, 0);
    else if (len == 3) sort_three(a);
    else sort_stacks(a, &b);
    free_stack(&b);
}

/* ================== MAIN ================== */

int main(int argc, char **argv)
{
    t_list *a = NULL;
    char **args = argv + 1;

    if (argc == 1) return 0;
    if (argc == 2) args = split(argv[1], ' ');
    
    for (int i = 0; args[i]; i++)
    {
        long n = ft_atol(args[i]);
        if (n < INT_MIN || n > INT_MAX) error_exit(&a);
        append_node(&a, n);
    }
    
    push_swap(&a);
    free_stack(&a);
    return 0;
}
