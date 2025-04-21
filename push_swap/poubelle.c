#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

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
}               t_list;

int     error_syntax(char *s);
int     error_duplicate(t_list *a, int n);
void    free_stack(t_list **stack);
void    free_errors(t_list **a);
void    init_stack_a(t_list **a, char **argv);
char    **split(char *s, char c);
void    init_nodes_a(t_list *a, t_list *b);
void    init_nodes_b(t_list *a, t_list *b);
void    current_index(t_list *stack);
void    set_cheapest(t_list *stack);
t_list  *get_cheapest(t_list *stack);
void    prep_for_push(t_list **s, t_list *n, char c);
int     stack_len(t_list *stack);
t_list  *find_last(t_list *stack);
int     stack_sorted(t_list *stack);
t_list  *find_min(t_list *stack);
t_list  *find_max(t_list *stack);
void    sa(t_list **a, int print);
void    sb(t_list **b, int print);
void    ss(t_list **a, t_list **b, int print);
void    ra(t_list **a, int print);
void    rb(t_list **b, int print);
void    rr(t_list **a, t_list **b, int print);
void    rra(t_list **a, int print);
void    rrb(t_list **b, int print);
void    rrr(t_list **a, t_list **b, int print);
void    pa(t_list **a, t_list **b, int print);
void    pb(t_list **b, t_list **a, int print);
void    sort_three(t_list **a);
void    sort_stacks(t_list **a, t_list **b);
void    print_list(t_list *a);

int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int error_syntax(char *s)
{
    if (!(*s == '+' || *s == '-' || ft_isdigit(*s)))
        return (1);
    if ((*s == '+' || *s == '-') && !ft_isdigit(s[1]))
        return (1);
    while (*++s)
        if (!ft_isdigit(*s))
            return (1);
    return (0);
}

int error_duplicate(t_list *a, int n)
{
    while (a)
    {
        if (a->nbr == n)
            return (1);
        a = a->next;
    }
    return (0);
}

void free_stack(t_list **stack)
{
    t_list *cur;
    t_list *tmp;

    if (!stack || !*stack)
        return;
    cur = *stack;
    while (cur)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    *stack = NULL;
}

void free_errors(t_list **a)
{
    free_stack(a);
    write(1, "Error\n", 6);
    exit(1);
}

static long ft_atol(const char *s)
{
    long    res;
    int     sign;

    res = 0;
    sign = 1;
    while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
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

static void append_node(t_list **stack, int n)
{
    t_list *node;
    t_list *last;

    node = malloc(sizeof(*node));
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
        last = find_last(*stack);
        last->next = node;
        node->prev = last;
    }
}

void init_stack_a(t_list **a, char **argv)
{
    long n;
    int  i;

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

static int count_words(char *s, char c)
{
    int count;
    int in;

    count = 0;
    while (*s)
    {
        in = 0;
        while (*s == c)
            s++;
        while (*s && *s != c)
        {
            if (!in)
            {
                count++;
                in = 1;
            }
            s++;
        }
    }
    return (count);
}

static char *get_next_word(char *s, char c)
{
    static int  cur;
    char        *word;
    int         len;
    int         i;

    len = 0;
    i = 0;
    while (s[cur] == c)
        cur++;
    while (s[cur + len] && s[cur + len] != c)
        len++;
    word = malloc(len + 1);
    if (!word)
        return (NULL);
    while (s[cur] && s[cur] != c)
        word[i++] = s[cur++];
    word[i] = '\0';
    return (word);
}

char **split(char *s, char c)
{
    char    **res;
    int     wc;
    int     i;

    wc = count_words(s, c);
    if (wc == 0)
        exit(1);
    res = malloc(sizeof(char *) * (wc + 2));
    if (!res)
        return (NULL);
    i = 0;
    while (wc-- >= 0)
    {
        if (i == 0)
        {
            res[i] = malloc(1);
            if (!res[i])
                return (NULL);
            res[i++][0] = '\0';
            continue;
        }
        res[i++] = get_next_word(s, c);
    }
    res[i] = NULL;
    return (res);
}

int stack_len(t_list *stack)
{
    int i;

    i = 0;
    while (stack)
    {
        stack = stack->next;
        i++;
    }
    return (i);
}

t_list *find_last(t_list *s)
{
    while (s && s->next)
        s = s->next;
    return (s);
}

int stack_sorted(t_list *s)
{
    while (s && s->next)
    {
        if (s->nbr > s->next->nbr)
            return (0);
        s = s->next;
    }
    return (1);
}

t_list *find_min(t_list *s)
{
    long    min;
    t_list  *m;

    if (!s)
        return (NULL);
    min = LONG_MAX;
    while (s)
    {
        if (s->nbr < min)
        {
            min = s->nbr;
            m = s;
        }
        s = s->next;
    }
    return (m);
}

t_list *find_max(t_list *s)
{
    long    max;
    t_list  *m;

    if (!s)
        return (NULL);
    max = LONG_MIN;
    while (s)
    {
        if (s->nbr > max)
        {
            max = s->nbr;
            m = s;
        }
        s = s->next;
    }
    return (m);
}

static void push(t_list **dst, t_list **src)
{
    t_list *n;

    if (!*src)
        return;
    n = *src;
    *src = (*src)->next;
    if (*src)
        (*src)->prev = NULL;
    n->prev = NULL;
    if (!*dst)
    {
        *dst = n;
        n->next = NULL;
    }
    else
    {
        n->next = *dst;
        (*dst)->prev = n;
        *dst = n;
    }
}

void pa(t_list **a, t_list **b, int p)
{
    push(a, b);
    if (!p)
        write(1, "pa\n", 3);
}

void pb(t_list **b, t_list **a, int p)
{
    push(b, a);
    if (!p)
        write(1, "pb\n", 3);
}

static void rev_rotate(t_list **s)
{
    t_list *last;

    if (!*s || !(*s)->next)
        return;
    last = find_last(*s);
    last->prev->next = NULL;
    last->next = *s;
    last->prev = NULL;
    (*s)->prev = last;
    *s = last;
}

void rra(t_list **a, int p)
{
    rev_rotate(a);
    if (!p)
        write(1, "rra\n", 4);
}

void rrb(t_list **b, int p)
{
    rev_rotate(b);
    if (!p)
        write(1, "rrb\n", 4);
}

void rrr(t_list **a, t_list **b, int p)
{
    rev_rotate(a);
    rev_rotate(b);
    if (!p)
        write(1, "rrr\n", 4);
}

static void rotate(t_list **s)
{
    t_list *last;

    if (!*s || !(*s)->next)
        return;
    last = find_last(*s);
    last->next = *s;
    (*s)->prev = last;
    *s = (*s)->next;
    (*s)->prev->next = NULL;
    (*s)->prev = NULL;
}

void ra(t_list **a, int p)
{
    rotate(a);
    if (!p)
        write(1, "ra\n", 3);
}

void rb(t_list **b, int p)
{
    rotate(b);
    if (!p)
        write(1, "rb\n", 3);
}

void rr(t_list **a, t_list **b, int p)
{
    rotate(a);
    rotate(b);
    if (!p)
        write(1, "rr\n", 3);
}

static void swap(t_list **h)
{
    t_list *second;

    if (!*h || !(*h)->next)
        return;
    second = (*h)->next;
    (*h)->next = second->next;
    if (second->next)
        second->next->prev = *h;
    second->prev = NULL;
    second->next = *h;
    (*h)->prev = second;
    *h = second;
}

void sa(t_list **a, int p)
{
    swap(a);
    if (!p)
        write(1, "sa\n", 3);
}

void sb(t_list **b, int p)
{
    swap(b);
    if (!p)
        write(1, "sb\n", 3);
}

void ss(t_list **a, t_list **b, int p)
{
    swap(a);
    swap(b);
    if (!p)
        write(1, "ss\n", 3);
}

void sort_three(t_list **a)
{
    t_list *mx;

    mx = find_max(*a);
    if (mx == *a)
        ra(a, 0);
    else if ((*a)->next == mx)
        rra(a, 0);
    if ((*a)->nbr > (*a)->next->nbr)
        sa(a, 0);
}

/* rest of sort_stacks and helper functions omitted for lisibility */

void print_list(t_list *a)
{
    while (a)
    {
        printf("%d ", a->nbr);
        a = a->next;
    }
    write(1, "\n", 1);
}

int main(int argc, char **argv)
{
    t_list  *a;
    t_list  *b;

    a = NULL;
    b = NULL;
    if (argc < 2 || (argc == 2 && !argv[1][0]))
        return (1);
    if (argc == 2)
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
