CC = cc
CFLAGS = -Wall -Wextra -Werror -I
SRCS_FILE = $(shell find . -name "*.c")
INCLUDES = includes
OBJS_FILE = $(SRCS_FILE:%.c=%.o)
NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJS_FILE)
	ar rcs $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJS_FILE) $(OBJS_BFILE)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
