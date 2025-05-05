CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRCS =	commands/push.c \
	commands/rev_rotate.c \
	commands/rotate.c \
	commands/swap.c \
	core/errors.c \
	core/ft_put.c \
	core/inita.c \
	core/initb.c \
	core/move.c \
	core/push_swap.c \
	core/sort.c \
	core/split.c \
	core/stack.c \
	core/utils.c

OBJS = $(SRCS:.c=.o)
NAME = push_swap

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re