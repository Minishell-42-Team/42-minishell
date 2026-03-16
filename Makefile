NAME            = minishell
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Iincludes -Ilibft
LDFLAGS         = -Llibft -lft -lreadline

SRCS            = $(shell find ./srcs -name "*.c" | grep -v "4_Built-in")
OBJS            = $(SRCS:%.c=%.o)
INC_DIR         = includes
LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/libft.a

BUILTIN_DIR     = srcs/4_Built-in
BUILTIN_LIB     = $(BUILTIN_DIR)/builtin.a

GREEN           = \033[0;32m
RED             = \033[0;31m
YELLOW          = \033[0;33m
RESET           = \033[0m

all: $(LIBFT) $(BUILTIN_LIB) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(BUILTIN_LIB):
	@echo "$(YELLOW)Compiling built-ins...$(RESET)"
	@$(MAKE) -C $(BUILTIN_DIR)

$(NAME): $(OBJS) $(BUILTIN_LIB) $(LIBFT)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(BUILTIN_LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Deleting object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(BUILTIN_DIR) clean

fclean: clean
	@echo "$(RED)Deleting $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(BUILTIN_DIR) fclean

re: fclean all

debug: CFLAGS += -g3 -fsanitize=address
debug: re

gdb: CFLAGS += -g3
gdb: re

.PHONY: all clean fclean re
