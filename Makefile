NAME            = minishell
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Iincludes -Ilibft -Isrcs/5_Builtins
LDFLAGS         = -Llibft -lft -lreadline

SRCS            = $(shell find ./srcs -name "*.c" | grep -v "5_Builtins")
OBJS            = $(SRCS:%.c=%.o)
INC_DIR         = includes
LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/libft.a

BUILTIN_DIR     = srcs/5_Builtins
BUILTIN_LIB     = $(BUILTIN_DIR)/builtin.a

GREEN           = \033[0;32m
RED             = \033[0;31m
YELLOW          = \033[0;33m
RESET           = \033[0m

all: $(LIBFT) $(BUILTIN_LIB) $(NAME)

$(LIBFT):
	@printf "$(YELLOW)Compiling libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(BUILTIN_LIB):
	@printf "$(YELLOW)Compiling built-ins...$(RESET)\n"
	@$(MAKE) -C $(BUILTIN_DIR)

$(NAME): $(OBJS) $(BUILTIN_LIB) $(LIBFT)
	@printf "$(YELLOW)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(OBJS) $(BUILTIN_LIB) $(LDFLAGS) -o $(NAME)
	@printf "$(GREEN)$(NAME) created successfully!$(RESET)\n"

%.o: %.c
	@printf "$(YELLOW)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)Deleting object files...$(RESET)\n"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(BUILTIN_DIR) clean

fclean: clean
	@printf "$(RED)Deleting $(NAME)...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(BUILTIN_DIR) fclean

re: fclean all

debug: CFLAGS += -g3 -fsanitize=address
debug: re

gdb: CFLAGS += -g3
gdb: re

test: re
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./minishell


.PHONY: all clean fclean re
