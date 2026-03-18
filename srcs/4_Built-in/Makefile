NAME = builtin.a
TEST_NAME = test_builtin

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../../includes -I ../../libft
LDFLAGS = -L../../libft -lft

SRCS = export.c utils_env_vars.c unset.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	$(CC) $(CFLAGS) tests/test_builtin.c $(NAME) $(LDFLAGS) -o $(TEST_NAME)
	@echo "Test executable created: ./$(TEST_NAME)"

clean:
	rm -f $(OBJS) tests/*.o

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
