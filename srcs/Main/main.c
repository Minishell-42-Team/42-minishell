#include "minishell.h"

int g_status = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_status = 0;
}

void	check_builtin_and_do(t_command_ast *cmds, char **envp)
{
	if (ft_strcmp(cmds->command, "export") == 0 && !cmds->args)
		ft_export(NULL, envp);
	else if (ft_strcmp(cmds->command, "unset") == 0)
		return ;

}

void	do_commands(t_command_ast *cmds, char **envp)
{
	t_command_ast *node;

	node = cmds;
	while (node)
	{
		check_builtin_and_do(node, envp);
		node = node->next;
	}
}

static void	lp_read_loop(char *line, char **envp)
{
	t_token			*tokens;
	t_command_ast	*cmds;

	(void)envp;
	if (!line)
		exit(EXIT_SUCCESS);
	add_history(line);
	tokens = lexer(line);
	cmds = parser(tokens);
	print_commands(cmds);
	//do_commands(cmds, envp);
	ft_free_command(&cmds);
	free_tokens(tokens);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;

	if (signal(SIGINT, handle_signal) != 0
		|| signal(SIGQUIT, handle_signal) != 0)
		return (printf("error: fail to catch a signal.\n"), 1);
	line = NULL;
	while (1)
	{
		line = readline("minishell> ");
		lp_read_loop(line, envp);
		free(line);
	}
	rl_clear_history();
//	clear_history();
	return (g_status);
}
