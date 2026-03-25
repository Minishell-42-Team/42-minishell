/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/24 21:00:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

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

/*static int	check_builtin_and_do(t_command_ast *cmds, t_env_var **env,
		t_minishell_data **data)
{
	char	*arg;
	int		stdin_copy;
	int		stdout_copy;

// je verifie dabord que cest un builtin
	if (!cmds || !cmds->command)
		return (0);
	if (ft_strcmp(cmds->command, "echo") != 0
		&& ft_strcmp(cmds->command, "pwd") != 0
		&& ft_strcmp(cmds->command, "env") != 0
		&& ft_strcmp(cmds->command, "cd") != 0
		&& ft_strcmp(cmds->command, "export") != 0
		&& ft_strcmp(cmds->command, "unset") != 0
		&& ft_strcmp(cmds->command, "exit") != 0)
		return (0);
// Je sauvegarde stdin/stdout
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (cmds->redirs)
	{
		if (!apply_redirections(cmds->redirs))
		{
			dup2(stdin_copy, STDIN_FILENO);
			dup2(stdout_copy, STDOUT_FILENO);
			close(stdin_copy);
			close(stdout_copy);
			return (1);
		}
	}
// BUILTINS
	if (ft_strcmp(cmds->command, "echo") == 0)
		ft_echo(cmds->args);
	else if (ft_strcmp(cmds->command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->command, "env") == 0 && !cmds->args)
		ft_env(*env);
	else if (ft_strcmp(cmds->command, "cd") == 0)
	{
		arg = NULL;
		if (cmds->args)
			arg = (char *)cmds->args->content;
		ft_cd(arg, *env);
	}
	else if (ft_strcmp(cmds->command, "export") == 0)
	{
		if (!cmds->args)
			ft_export(NULL, env, NULL);
		else
			ft_export((char *)cmds->args->content,
				env, &(*data)->execdirs);
	}
	else if (ft_strcmp(cmds->command, "unset") == 0 && cmds->args->content)
		ft_unset(env, (char *)cmds->args->content);
	else if (ft_strcmp(cmds->command, "exit") == 0)
		ft_exit(data);
// Je restore
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (1);
}*/

static void	lp_read_loop(t_minishell_data **data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			return ;
		}
		add_history(line);
		(*data)->tokens = lexer(line, (*data)->envs);
		(*data)->cmds = parser((*data)->tokens);
		execute_pipeline((*data)->cmds, data);
		ft_free_command(&(*data)->cmds);
		free_tokens((*data)->tokens);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell_data	*data;
	int					i;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	data = (t_minishell_data *)malloc(sizeof(t_minishell_data));
	if (!data)
		return (EXIT_FAILURE);
	data->envs = NULL;
	data->execdirs = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	i = -1;
	while (envp[++i])
		ft_export(envp[i], &data->envs, &data->execdirs);
	lp_read_loop(&data);
	ft_free_envs(&data->envs);
	ft_lstclear(&data->execdirs, free);
	free(data);
	rl_clear_history();
	return (g_status);
}
