CC = cc
CFLAGS = -Wall -Wextra -Werror -I
SRCS_FILE = $(shell find . -name "*.c" ! -name "ft_lst*.c")
SRCS_BFILE = $(shell find . -name "ft_lst*.c")
INCLUDES = includes
OBJS_FILE = $(SRCS_FILE:%.c=%.o)
OBJS_BFILE = $(SRCS_BFILE:%.c=%.o)
NAME = libft.a

all : $(NAME)

bonus : $(OBJS_BFILE)
	ar rcs $(NAME) $^

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
