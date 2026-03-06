#include "minishell.h"

int g_status = 0;

int main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
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
		printf("You entered: %s\n", line);
		free(line);
	}
	rl_clear_history();
	return (g_status);
}
