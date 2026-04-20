NAME = builtin.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../../includes -I ../../libft
LDFLAGS = -L../../libft -lft

SRCS = export.c utils_env_vars.c env_to_array.c unset.c env.c  \
	   pwd.c echo.c cd.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
