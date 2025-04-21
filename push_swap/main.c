# include <stdbool.h> //To use bool flags, e.g, to print or not to print
# include <limits.h> //To define MIN and MAX macros
#include <stdio.h>
#include <stdlib.h>

typedef struct s_stack_node //A container of data enclosed in {} braces. `s_` for struct
{
	int					nbr; //The number to sort
	int					index; //The number's position in the stack
	int					push_cost; //How many commands in total
	bool				above_median; //Used to calculate `push_cost`
	bool				cheapest; //The node that is the cheapest to do commands
	struct s_stack_node	*target_node; //The target node of a node in the opposite stack
	struct s_stack_node	*next; //A pointer to the next node
	struct s_stack_node	*prev; //A pointer to the previous node
}	t_stack_node; //The "shortened name", "t_stack_node". `t_` for type

//***Handle errors
int				error_syntax(char *str_n); 
int				error_duplicate(t_stack_node *a, int n);
void			free_stack(t_stack_node **stack);
void			free_errors(t_stack_node **a);

//***Stack initiation
void			init_stack_a(t_stack_node **a, char **argv); //Initiate stack `a` before processing
char			**split(char *s, char c); //To handle input of numbers as a string argument, e.g. enclosed in " "

//***Nodes initiation
void			init_nodes_a(t_stack_node *a, t_stack_node *b); //To prep all nodes for pushing `a` to `b`
void			init_nodes_b(t_stack_node *a, t_stack_node *b); //To prep all nodes for pushing `b` back to `a`
void			current_index(t_stack_node *stack); //Set the node's current index
void			set_cheapest(t_stack_node *stack); //Set the stack's cheapest node
t_stack_node	*get_cheapest(t_stack_node *stack); //Get the cheapest node of a stack
void			prep_for_push(t_stack_node **s, t_stack_node *n, char c); //Prep the required nodes on top for pushing

//***Stack utils
int				stack_len(t_stack_node *stack); //Calculate the length of a stack
t_stack_node	*find_last(t_stack_node *stack); //Find the last node of a stack
bool			stack_sorted(t_stack_node *stack); //To check whether a stack is sorted
t_stack_node	*find_min(t_stack_node *stack); //Find the smallest number
t_stack_node	*find_max(t_stack_node *stack); //Find the biggest number

//***Commands
void			sa(t_stack_node **a, bool print);
void			sb(t_stack_node **b, bool print);
void			ss(t_stack_node **a, t_stack_node **b, bool print);
void			ra(t_stack_node **a, bool print);
void			rb(t_stack_node **b, bool print);
void			rr(t_stack_node **a, t_stack_node **b, bool print);
void			rra(t_stack_node **a, bool print);
void			rrb(t_stack_node **b, bool print);
void			rrr(t_stack_node **a, t_stack_node **b, bool print);
void			pa(t_stack_node **a, t_stack_node **b, bool print);
void			pb(t_stack_node **b, t_stack_node **a, bool print);

//***Algorithm
void			sort_three(t_stack_node **a);
void			sort_stacks(t_stack_node **a, t_stack_node **b); //Turk algorithm


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	error_syntax(char *str_n) //Define a funtion to handle syntax errors, and returns `1` for `error` should any of the following conditions are met
{
	if (!(*str_n == '+'
			|| *str_n == '-'
			|| (*str_n >= '0' && *str_n <= '9'))) //Check if the first character of the input string does not contain a sign or a digit
		return (1);
	if ((*str_n == '+'
			|| *str_n == '-')
		&& !(str_n[1] >= '0' && str_n[1] <= '9')) //Check if the first character of the input string contains a sign, but the second character does not contain a digit
		return (1);
	while (*++str_n) //If the error conditions above are passed, pre-increment to point to the next character in the string, and loop until the end of the string is reached
	{
		if (!(*str_n >= '0' && *str_n <= '9')) //Check if the next character in the string is not a digit
			return (1);
	}
	return (0);
}

int	error_duplicate(t_stack_node *a, int n) //Define a function that checks for duplicate input numbers in stack `a`
{
	if (!a) //Check for an empty stack
		return (0);
	while (a) //Loop until the end of stack `a` is reached
	{
		if (a->nbr == n) //Check if the current node's value is equal to `n`. Refer to `init_stack_a()`
			return (1);
		a = a->next; //Move to the next node to check for duplicates
	}
	return (0);
}

void	free_stack(t_stack_node **stack) //Define a function to free a stack if there are errors
{
	t_stack_node	*tmp; //To store the next node in the stack before the current node is freed, because once a node is freed, you can't access its next pointer
	t_stack_node	*current;

	if (!stack) //Check for an empty stack
		return ;
	current = *stack;
	while (current) //As long as a node exist in the stack
	{
		tmp = current->next; //Assign to `tmp` the pointer to the next node
		current->nbr = 0; //Assigning the node to `0` before freeing is not strictly necessary but it can help catch potential bugs such as memory-leaks and improve debugging
		free(current); //Free the current node, deallocating the memory occupied by that node
		current = tmp; //Assign `tmp` as the current first node
	}
	*stack = NULL;
}

void	free_errors(t_stack_node **a) //Define a function that, upon encountering a unique error, to free the stack and print an error message
{
	free_stack(a);
	printf("Error\n");
	exit(1);
}

void	current_index(t_stack_node *stack)
{
	int	i; //To store the index of the current node
	int	median; //To store the position of the median of the stack

	i = 0; //The first index is `0`
	if (!stack) //Check for am empty stack
		return ;
	median = stack_len(stack) / 2; //Calculate the median by dividing the length of a stack by 2
	while (stack) //Loop through all the nodes until the end of the stack is reached
	{
		stack->index = i; //Assign the current index value to the current node
		if (i <= median) //Check whether the current node is above or below the median
			stack->above_median = true; //If above, set the above_median data of the node to true
		else
			stack->above_median = false; //If below, set the above_median data of the node to false
		stack = stack->next; //Move to the next node for indexing
		++i; //Increment the index value to set the next node with
	}
}

static void	set_target_a(t_stack_node *a, t_stack_node *b)//Find `a` node's target in stack `b`
{
	t_stack_node	*current_b; //To store the pointer to the current node in stack `b` and iterate through each node following
	t_stack_node	*target_node; //To store the pointer to the target node in stack `b`
	long			best_match_index; //In this case, the best match indexe stores the value of the "closest smaller number" so far

	while (a) //As long as we have nodes in stack `a`
	{
		best_match_index = LONG_MIN; //Assign the smallest `long` as the closest smaller number so far
		current_b = b; //Assign to `current_b` the current `b` node
		while (current_b) //Iteratively search through all the nodes in stack `b` until the end of the stack is reached
		{
			if (current_b->nbr < a->nbr 
				&& current_b->nbr > best_match_index) //Check if `b` node is smaller than `a` node && bigger than the closest smaller number so far
			{
				best_match_index = current_b->nbr; //If so, update the value of the closest smaller number so far
				target_node = current_b; //Assign the current `b` node as the `target_node`
			}
			current_b = current_b->next; //Move to the next `b` node for comparison, until a "closer smaller number" is found
		}
		if (best_match_index == LONG_MIN) //Check if the LONG_MIN hasn't changed, it means we haven't found anything smaller
			a->target_node = find_max(b); //If so, find the biggest `nbr` and set this as the target node
		else
			a->target_node = target_node; //If no "closer smaller number" is found, and the best match has changed
		a = a->next; //Move to the next `a` node to find it's target `b` node
	}
}

static void	cost_analysis_a(t_stack_node *a, t_stack_node *b) //Define a functio that analyses the cost of the `a` node along with it's target `b` node, which is the sum of the number of instructions for both the nodes to rotate to the top of their stacks
{
	int	len_a; //To store the length of stack `a`
	int	len_b; //To store the length of stack `b`

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a) //Loop through each node until the end of the stack is reached
	{
		a->push_cost = a->index; //Assign the current `a` node's push cost, its' index value
		if (!(a->above_median)) //Check if the above_median data is false, meaning it is below median
			a->push_cost = len_a - (a->index); //If so, update `a` node's push cost to the stack's length - index
		if (a->target_node->above_median) //Check if `a` node's target node `b` has a "true" above median attribute, meaning the target `b` node is above median
			a->push_cost += a->target_node->index; //If so, update `a` node's push cost, the sum of (its current index) + (its target `b` node's index)
		else //If `a` node is indeed above median and its target `b` node is below median
			a->push_cost += len_b - (a->target_node->index); //Update `a` node's push cost, the sum of (its current index) + (`b` stack's length - its target `b` node's index)
		a = a->next; //Move to the next `a` node for its cost analysis
	}
}

void	set_cheapest(t_stack_node *stack) //Define a function that sets a node's `cheapest` attribute as `true` or `false`
{
	long			cheapest_value; //To store the value of the cheapest node so far
	t_stack_node	*cheapest_node; //To store a pointer to the cheapest node so far

	if (!stack) //Check for an empty stack
		return ;
	cheapest_value = LONG_MAX; //Assign the biggest `long` as the cheapest value so far
	while (stack) //Loop through every node until the end of the stack is reached, and we find the cheapest node
	{
		if (stack->push_cost < cheapest_value) //Check if the current node's push cost is cheaper than the cheapest value so far
		{
			cheapest_value = stack->push_cost; //If so, update the cheapest value to the current node's push cost
			cheapest_node = stack; //Assign the current node as the cheapest node so far
		}
		stack = stack->next; //Move to the next node for comparison
	}
	cheapest_node->cheapest = true; //After iterating through the stack, if no cheaper node is found than the current, then set the cheapest node's `cheapest` attribut to `true` in the data structure
}

void	init_nodes_a(t_stack_node *a, t_stack_node *b) //Define a function that combines all the functions needed to prepare stack `a`, ready for our pushing and sorting. These functions set the data inside the node's structure
{
	current_index(a);
	current_index(b);
	set_target_a(a, b);
	cost_analysis_a(a, b);
	set_cheapest(a);
}

static void	set_target_b(t_stack_node *a, t_stack_node *b) //Define a function that sets for the current `a` node, its target node from stack `a`
{
	t_stack_node	*current_a; //To store the pointer to the current `a` node
	t_stack_node	*target_node; //To store the pointer of the target node for `b` node
	long			best_match_index; //To store the "closest bigger" number so far

	while (b)
	{
		best_match_index = LONG_MAX; //Set the current best match to the max long
		current_a = a; //Assign the pointer to point to the current `a` node
		while (current_a) //While the pointer is not set to NULL
		{
			if (current_a->nbr > b->nbr 
				&& current_a->nbr < best_match_index) //Check if the `a` node's value is bigger than `b` node, && smaller than the "closest bigger" so far
			{
				best_match_index = current_a->nbr; //Set the best match as the value in the current `a` node
				target_node = current_a; //Set `b` node's target node pointer to point to the current `a` node
			}
			current_a = current_a->next; //Move to the next `a` node for processing
		}
		if (best_match_index == LONG_MAX) //If the best match value has not changed
			b->target_node = find_min(a); //Set `b` node's target node pointer to point to the smallest number in stack `a`
		else
			b->target_node = target_node; //If the best match value has been updated, then we have a target node for the current `b` node
		b = b->next; //Move to the next `b` node for processing
	}
}

void	init_nodes_b(t_stack_node *a, t_stack_node *b) //Define a function that prepares the nodes for pushing `b` to `a`
{
	current_index(a);
	current_index(b);
	set_target_b(a, b);
}

static int	count_words(char *s, char c) //Define a function that returns the substrings count in a string seperated by a delimiter
{
	int		count; //To store the substring count
	bool	inside_word; //A flag to indicate whether we are inside a substring or a delimeter

	count = 0;
	while (*s) //Loop until the end of the string is reached
	{
		inside_word = false; //Set the bool to false to start the loop
		while (*s == c) //While the current character is the delimeter
			++s; //Move to the next character
		while (*s != c && *s) //While the current character is not a deilimeter and the end of the string is not reached, 
		{
			if (!inside_word) //If we are not currently inside the substring
			{
				++count; //Increment the count as we are about to move inside a substring
				inside_word = true; //Set the bool to true, indicating we've found a substring
			}
			++s; //Move to the next character of the string
		}
	}
	return (count);
}

static char	*get_next_word(char *s, char c) //Define a function that returns the new substring found within a string
{
	static int	cursor = 0; //To keep track of the position within the string `s` across multiple function calls, needed to continue processing the string from where we left off in previous calls, essential for tokenizing a string
	char		*next_word; //To store a pointer of the new substring
	int			len; //To store the length of the substring being extracted
	int			i; //Used for indexing characters in the new substring

	len = 0;
	i = 0;
	while (s[cursor] == c) //Skip past any consecutive delimiter characters at the current position in the string
		++cursor;
	while ((s[cursor + len] != c) && s[cursor + len]) //Calculate the length of the substring by counting characters until either a delimiter or the end of the string is encountered
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1); //Allocate memory for new substring based on its length plus one byte for the null terminator
	if (!next_word) //Check for unsuccessful memory allocation
		return (NULL);
	while ((s[cursor] != c) && s[cursor]) //Loop until a delimeter is encountered and the end of the string is reached
		next_word[i++] = s[cursor++]; //Copy each character from the string to the new substring and increment `i` and `cursor` after each character
	next_word[i] = '\0'; //Properly null terminate the newly created substring
	return (next_word);
}

char **split(char *s, char c) //Define a function that returns the substrings in a string seperated by a delimiter
{
	int		words_count; //Used to keep track of the number of substrings in the string
	char	**result_array; //To store a pointer to pointers, the array of all the substrings
	int		i; //Used to iterate through the array

	i = 0;
	words_count = count_words(s, c);
	if (!words_count) //Check for `0` words
		exit(1);
	result_array = malloc(sizeof(char *) * (size_t)(words_count + 2)); //Allocate memory for the result_array based on the number of words (words_count) plus two additional slots to account for the null terminator at the end of the last string, and to null terminate the entire array
	if (!result_array) //Check for unsuccessful memory allocation
		return (NULL);
	while (words_count-- >= 0) //Iterates through the words to be split all words have been processed
	{
		if (i == 0) //Check if the first character of the input string is the delimiter
		{
			result_array[i] = malloc(sizeof(char)); //Allocate memory for an empty string (a single null terminator)
			if (!result_array[i]) ////Check for unsuccessful memory allocation
				return (NULL);
			result_array[i++][0] = '\0'; //Include in the result array as distinct elements
			continue ;
		}
		result_array[i++] = get_next_word(s, c); //If the first character of the string is not a delimeter, extract the substring and copy it into the result array
	}
	result_array[i] = NULL; //Properly null terminate the array
	return (result_array);
}

static long	ft_atol(const char *s) //Define a function that converts every string into a long value
{
	long	result;
	int		sign;

	result = 0;
	sign = 1; 
	while (*s == ' ' || *s == '\t' || *s == '\n' || \
			*s == '\r' || *s == '\f' || *s == '\v')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

static void	append_node(t_stack_node **stack, int n) //Define a function that searches for the last node to append to the linked list
{
	t_stack_node	*node; //To store a pointer to the new node to be created with the value `n`
	t_stack_node	*last_node; //To store a pointer to the current last node of the stack

	if (!stack)
		return ;
	node = malloc(sizeof(t_stack_node)); //Allocate memory for the new node
	if (!node)
		return ;
	node->next = NULL; //Set the next pointer of the new node to NULL because it will be the last node in the list
	node->nbr = n; //Set the `next` data of of the new node to `n` value
	node->cheapest = 0; // Initialise chaepest to 0;
	// other elements in the struct could be initialised as well but for now, this was the only one causing a valgrind issue
	if (!(*stack)) //Check if the stack is empty or currently pointing to NULL, indicating a first node needs to be found
	{
		*stack = node; //If empty, update the pointer *stack to point to the node, effectively making it the new head of the linked list
		node->prev = NULL; //Set the head node's previous pointer to NULL as it's the first node
	}
	else //If the stack is not empty, it means there are existing nodes in the linked list
	{
		last_node = find_last(*stack); //In which case, find the last node
		last_node->next = node; //Append the new node to the last node
		node->prev = last_node; //Update the previous pointer of the new node and complete the appending
	}
}

void	init_stack_a(t_stack_node **a, char **argv) //Define a function that initiates stack `a` by handling any errors and appending required nodes to complete a stack
{
	long	n;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			free_errors(a);
		n = ft_atol(argv[i]);
		if (n > INT_MAX || n < INT_MIN) //Check for overflow
			free_errors(a);
		if (error_duplicate(*a, (int)n))
			free_errors(a); 
		append_node(a, (int)n); //If no errors, append the node to the linked list by, taking a pointer to stack `a`, create a new node and assign `n` to that new node
		i++;
	}
}

t_stack_node	*get_cheapest(t_stack_node *stack) //Define a function that searches for the cheapest node, that is set by bool
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

void	prep_for_push(t_stack_node **stack,
						t_stack_node *top_node,
						char stack_name) //Define a function that moves the required node to the top of the stack
{
	while (*stack != top_node) //Check if the required node is not already the first node
	{
		if (stack_name == 'a') //If not, and it is stack `a`, execute the following
		{
			if (top_node->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b') //If not, and it is stack `b`, execute the following
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}	
	}
}

int	stack_len(t_stack_node *stack) //Define a function that calculates and returns the length of a stack
{
	int	count; //To store the node count

	if (!stack) 
		return (0);
	count = 0;
	while (stack) //Loop until the end of the stack is reached
	{
		stack = stack->next; //Move to the next node
		count++;
	}
	return (count);
}

t_stack_node	*find_last(t_stack_node *stack) //Define a function that returns the pointer to the last node
{
	if (!stack)
		return (NULL);
	while (stack->next) //Loop until the end of the stack is reached
		stack = stack->next;
	return (stack);
}

bool	stack_sorted(t_stack_node *stack) //Define a function that checks if the stack is sorted in ascending order
{
	if (!stack)
		return (1);
	while (stack->next) //Loop until the end of the stack is reached
	{
		if (stack->nbr > stack->next->nbr) //Check if the current value is larger than the next node's value, indicating it is out of sort
			return (false);
		stack = stack->next; //If not, move to the next node for processing
	}
	return (true);
}

t_stack_node	*find_min(t_stack_node *stack) //Define a function that searches a stack and returns the node with the smallest number
{
	long			min; //To store the smallest value so far
	t_stack_node	*min_node; //To store a pointer that points to the smallest number

	if (!stack)
		return (NULL);
	min = LONG_MAX; //Assign to the smallest value so far, the max long integer
	while (stack) //Loop until the end of the stack is reached
	{
		if (stack->nbr < min) //Check if the current node value is smaller than the smallest so far
		{
			min = stack->nbr; //If so, update the smallest number so far
			min_node = stack; //Set the pointer to point to the node with the smallest number so far
		}
		stack = stack->next; //Move to the next node for processing
	}
	return (min_node); 
}

t_stack_node	*find_max(t_stack_node *stack) //Define a function that searches a stack and returns the node with the biggest number
{
	long			max; //To store the biggest value so far
	t_stack_node	*max_node; //To store a pointer that points to the biggest number

	if (!stack)
		return (NULL);
	max = LONG_MIN; //Assign to the biggest value so far, the max long integer
	while (stack) //Loop until the end of the stack is reached
	{
		if (stack->nbr > max) //Check if the current node value is smaller than the biggest so far
		{
			max = stack->nbr; //If so, update the biggest number so far
			max_node = stack; //Set the pointer to point to the node with the biggest number so far
		}
		stack = stack->next; //Move to the next node for processing
	}
	return (max_node);
}

static void	push(t_stack_node **dst, t_stack_node **src) //Define a function that pushes a top node, from one stack to another's top node
{
	t_stack_node	*push_node; //Used to store the pointer to the node to be pushed

	if (!*src) //The top node of a stack to be pushed
		return ;
	push_node = *src; //The top node to push is assigned to the `t_stack_node` variable
	*src = (*src)->next; //Move the pointer of the stack to the next node, which will become the next `top node` after the node before is "popped off"
	if (*src) //Check if the current node exists
		(*src)->prev = NULL; //Set the current node as the head of the stack
	push_node->prev = NULL; //Detach the node to push from its stack
	if (!*dst) //Check if the other stack is empty
	{
		*dst = push_node; //If it's empty, assign as the first node of that stack, the node we want pushed
		push_node->next = NULL; //Ensure it is also set as the last node, e.g. properly null terminate the stack
	}
	else //If the other stack we want to push to is not empty
	{
		push_node->next = *dst; //Assign the node to push, to the top of the current top node of the stack
		push_node->next->prev = push_node; //Assign to the "second node" `prev` attribute, the pushed node as the current top node
		*dst = push_node; //Complete appending the node. The pointer to the top node of the stack is now pointing to our recently pushed node
	}
}

void	pa(t_stack_node **a, t_stack_node **b, bool print) //Push on top of `b`, the top `a` and print the instruction
{
	push(a, b); 
	if (!print) 
		printf("pa\n");
}

void	pb(t_stack_node **b, t_stack_node **a, bool print) //Push on top of `a`, the top `b` and print the instruction
{
	push(b, a);
	if (!print)
		printf("pb\n");
}

static void	rev_rotate(t_stack_node **stack) //Define a funtion that rotates a stack's bottom node, to the top
{
	t_stack_node	*last; //To store the pointer to the last node

	if (!*stack || !(*stack)->next) //Check if the stack is empty, or if there's one node
		return ;
	last = find_last(*stack);
	last->prev->next = NULL; //Assign to the `next` attribute of the node before itself, `NULL` effectively setting it as the current last node
	last->next = *stack; //Assign to its own `next` attribute as the top node of the stack
	last->prev = NULL; //Detach itself from the node before it
	*stack = last;  //Complete appending itself to the top of the stack, and now holds the pointer to the top node
	last->next->prev = last; //Update the current last node of the stack
}

void	rra(t_stack_node **a, bool print) //Rotate the bottom of `a` to the top of the stack and print the instruction
{
	rev_rotate(a);
	if (!print)
		printf("rra\n");
}

void	rrb(t_stack_node **b, bool print) //Rotate the bottom of `b` to the top of the stack and print the instruction
{
	rev_rotate(b);
	if (!print)
		printf("rrb\n");
}

void	rrr(t_stack_node **a, t_stack_node **b, bool print) //Stimultaneously rotate both stacks' bottom nodes to the top of their stacks, halving the cost of instructions
{
	rev_rotate(a);
	rev_rotate(b);
	if (!print)
		printf("rrr\n");
}

static void	rotate(t_stack_node **stack) //Define a function that rotates the stack's top node to the bottom of the stack
{
	t_stack_node	*last_node; //To store a pointer to the last node of a stack

	if (!*stack || !(*stack)->next) //Check if the stack is empty, or if there's one node
		return ;
	last_node = find_last(*stack); 
	last_node->next = *stack; //Assign to the last node, its `next` attribute as the top node, effectively setting the current top node as the last node
	*stack = (*stack)->next; //Assign to the pointer of the top node, the node after it (second from the top)
	(*stack)->prev = NULL; //Complete setting the current top node by detaching it from its previous top node
	last_node->next->prev = last_node; //Reconnect the second node's prev pointer to point to what was previously the last node in the stack
	last_node->next->next = NULL; //Assign to the `next` attribute of the current last node, `NULL` effectively setting it as the current last node, and properly null terminating the stack
}		

void	ra(t_stack_node **a, bool print) //Rotate the top `a` node to the bottom of the stack, and print the instruction
{
	rotate(a);
	if (!print)
		printf("ra\n");
}

void	rb(t_stack_node **b, bool print) //Rotate the top `b` node to the bottom of the stack, and print the instruction
{
	rotate(b);
	if (!print)
		printf("rb\n");
}

void	rr(t_stack_node **a, t_stack_node **b, bool print) //Stimultaneously rotate both the top `a` and `b` nodes to the bottom of the stack, and print the instruction
{
	rotate(a);
	rotate(b);
	if (!print)
		printf("rr\n");
}

static void	swap(t_stack_node **head) //Define a function that swaps the positions of the top node and second node of a stack
{
	if (!*head || !(*head)->next) //Check if the stop node, or second node of a stack exists
		return ;
	*head = (*head)->next; //Update `head` to point to the next node, effectively swapping the first and second nodes
	(*head)->prev->prev = *head; //Update the `prev` pointer of the node before the `new head` to point to the `new head`
	(*head)->prev->next = (*head)->next; //Update the `next` pointer of the node before the `new head` to skip the `old head` and point directly to the `new head`
	if ((*head)->next) //Check if there's a `next` node after the `new head` and
		(*head)->next->prev = (*head)->prev; //If so, update its `prev` pointer to point back to the `new head`
	(*head)->next = (*head)->prev; //Update the `next` pointer of the `new head` to point to the `old head`, effectively reversing their positions
	(*head)->prev = NULL; //Sets the `prev` pointer of the `new head` to `NULL` completing the swap
}

void	sa(t_stack_node	**a, bool print) //Swap the first two nodes of stack `a` and print the instruction
{
	swap(a);
	if (!print)
		printf("sa\n");
}

void	sb(t_stack_node **b, bool print) //Swap the first two nodes of stack `b` and print the instruction
{
	swap(b);
	if (!print)
		printf("sb\n");
}

void	ss(t_stack_node **a, t_stack_node **b, bool print) //Stimutaneously swap the first two nodes of the stack and print the instruction
{
	swap(a);
	swap(b);
	if (!print)
		printf("ss\n");
}

void	sort_three(t_stack_node **a) //Define a function that handles when stack `a` has three nodes, and sorts it
{
	t_stack_node	*biggest_node; //To store a pointer to the biggest node in stack `a`

	biggest_node = find_max(*a);
	if (biggest_node == *a) //Check if the current node is the biggest
		ra(a, false); //If so, rotate the top node to the bottom of the stack
	else if ((*a)->next == biggest_node) //Check if the second node is the biggest
		rra(a, false); //If so, reverse rotate the bottom node, to the top of the stack
	if ((*a)->nbr > (*a)->next->nbr) //Check if the bottom node is the biggest, but the top node is higher than the second node
		sa(a, false); //If so, simply swap the top and second nodes
}

static void	rotate_both(t_stack_node **a,
    t_stack_node **b,
    t_stack_node *cheapest_node) //Define a function that rotates both the top `a` and `b` nodes to the bottom of their stacks, if it's the cheapest move
{
while (*b != cheapest_node->target_node
&& *a != cheapest_node) //As long as the current `b` node is not `a` cheapest node's target node, and the current top `a` node is not the top node
rr(a, b, false); //Rotate both `a` and `b` nodes
current_index(*a);
current_index(*b);
}

static void	rev_rotate_both(t_stack_node **a,
            t_stack_node **b,
            t_stack_node *cheapest_node) //Define a function that rotates both the bottom `a` and `b` nodes to the top of their stacks, if it's the cheapest move
{
while (*b != cheapest_node->target_node
&& *a != cheapest_node) //As long as the current `b` node is not `a` cheapest node's target node && and the current `a` node is not the cheapest
rrr(a, b, false); //Reverse rotate both `a` and `b` nodes
current_index(*a); //Refresh current node positions
current_index(*b);
}

static void	move_a_to_b(t_stack_node **a, t_stack_node **b) //Define a function that prepares the cheapest nodes on top of the stacks for pushing `a` nodes to stack `b`, until there are three nodes left in `a`
{
t_stack_node	*cheapest_node; //To store the pointer to the cheapest `a` node

cheapest_node = get_cheapest(*a); 
if (cheapest_node->above_median 
&& cheapest_node->target_node->above_median) //If both the cheapest `a` node and its target `b` node are above the median
rotate_both(a, b, cheapest_node);
else if (!(cheapest_node->above_median) 
&& !(cheapest_node->target_node->above_median)) //If both the cheapest `a` node and its target `b` node are below the median
rev_rotate_both(a, b, cheapest_node); //`rev_rotate_both` will execute if neither nodes are at the top
prep_for_push(a, cheapest_node, 'a'); //Ensure the cheapest nodes is at the top, ready for pushing
prep_for_push(b, cheapest_node->target_node, 'b'); //Ensure the target node is at the top, ready for pushing
pb(b, a, false);
}

static void	move_b_to_a(t_stack_node **a, t_stack_node **b) //Define a function that prepares `b`'s target `a` nodes for pushing all `b` nodes back to stack `a` 
{
prep_for_push(a, (*b)->target_node, 'a'); //Ensure `b`'s target `a` node is on top of the stack
pa(a, b, false); 
}

static void	min_on_top(t_stack_node **a) //Define a function that moves the smallest number to the top
{
while ((*a)->nbr != find_min(*a)->nbr) //As long as the smallest number is not at the top
{
if (find_min(*a)->above_median) //Rotate or reverse rotate according to the position of the node on the median
ra(a, false);
else
rra(a, false);
}
}

void	sort_stacks(t_stack_node **a, t_stack_node **b) //Define a function that sorts stack `a` if it has more than 3 nodes
{
int	len_a; //To store the length of stack `a`

len_a = stack_len(*a);
if (len_a-- > 3 && !stack_sorted(*a)) //If stack `a` has more than three nodes and aren't sorted
pb(b, a, false);
if (len_a-- > 3 && !stack_sorted(*a)) //If stack `a` still has more than three nodes and aren't sorted
pb(b, a, false);
while (len_a-- > 3 && !stack_sorted(*a)) //If stack `a` still has more than three nodes and aren't sorted
{
init_nodes_a(*a, *b); //Iniate all nodes from both stacks
move_a_to_b(a, b); //Move the cheapest `a` nodes into a sorted stack `b`, until three nodes are left in stack `a`
}
sort_three(a);
while (*b) //Until the end of stack `b` is reached
{
init_nodes_b(*a, *b); //Initiate all nodes from both stacks
move_b_to_a(a, b); //Move all `b` nodes back to a sorted stack `a`
}
current_index(*a); //Refresh the current position of stack `a`
min_on_top(a); //Ensure smallest number is on top
}

void	print_list(t_stack_node *a)
{
	while (a)
	{
		printf("%d ", a->nbr);
		a = a->next;
	}
	printf("\n");
}

int	main(int argc, char **argv) //Define a program that takes in a random input if numbers and sorts them in ascending order
{
	t_stack_node	*a; //To store a pointer to stack `a`
	t_stack_node	*b; //To store a pointer to stack `b`

	a = NULL; //Set both pointers to NULL to avoid undefined behaviour
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0])) //Check for incorrect argument counts or if the 2 argument is `0`
		return (1);
	else if (argc == 2) //Check if the argument count is 2 and the 2nd is not empty, this implies a string
		argv = split(argv[1], ' '); //Call ``split()` to extract each substring
	init_stack_a(&a, argv + 1); //Initiate stack `a`, which also handles errors
	if (!stack_sorted(a)) //Check if the stack is not sorted
	{
		if (stack_len(a) == 2) //If not, and there are two numbers, swap the first two nodes
			sa(&a, false);
		else if (stack_len(a) == 3) //If not, and there are three numbers, call the sort three algorithm
			sort_three(&a);
		else
			sort_stacks(&a, &b); //If not, and there are more than three numbers, call the sort stacks algorithm
	}
    print_list(a);
	free_stack(&a); //Clean up the stack
	return (0);
}