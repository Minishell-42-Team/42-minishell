#include "minishell.h"

int g_status = 0;

int main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;

	t_token *tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokens = lexer(line);
		print_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
	rl_clear_history();
//	clear_history();
	return (g_status);
}
