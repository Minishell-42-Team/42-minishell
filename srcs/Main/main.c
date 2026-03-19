/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/19 13:46:12 by clwenhaj         ###   ########.fr       */
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

static void	check_builtin_and_do(t_command_ast *cmds, t_env_var **env,
		t_minishell_data **data)

{
	char *arg;
	int stdin_copy;
	int stdout_copy;
	

	if (!cmds || !cmds->command)
		return ;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (cmds->redirs)
	{
		if (apply_redirections(cmds->redirs) < 0)
		{
			dup2(stdin_copy, STDIN_FILENO);
			dup2(stdout_copy, STDOUT_FILENO);
			close(stdin_copy);
			close(stdout_copy);
			return ;
		}
	}
	if (ft_strcmp(cmds->command, "export") == 0)
	{
		if (!cmds->args)
			ft_export(NULL, env);
		else
			ft_export((char *)cmds->args->content, env);
	}
	else if (ft_strcmp(cmds->command, "unset") == 0 && cmds->args && cmds->args->content)
		ft_unset(env, (char *)cmds->args->content);
	else if (ft_strcmp(cmds->command, "env") == 0 && !cmds->args)
		ft_env(*env);
	else if (ft_strcmp(cmds->command, "cd") == 0)
	{
		arg = NULL;
		if (cmds->args)
			arg = (char *)cmds->args->content;
		ft_cd(arg, *env);
	}
	else if (ft_strcmp(cmds->command, "echo") == 0)
		ft_echo(cmds->args);
	else if (ft_strcmp(cmds->command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->command, "exit") == 0)
		ft_exit(data);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}

static void	do_commands(t_minishell_data **data)
{
	t_command_ast	*node;

	node = (*data)->cmds;
	while (node)
	{
		check_builtin_and_do(node, &(*data)->envs, data);
		node = node->next;
	}
}

static void	lp_read_loop(t_minishell_data **data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			exit(EXIT_SUCCESS);
		add_history(line);
		(*data)->tokens = lexer(line);
		(*data)->cmds = parser((*data)->tokens);
		do_commands(data);
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
	if (signal(SIGINT, handle_signal) != 0
		|| signal(SIGQUIT, handle_signal) != 0)
		return (printf("error: fail to catch a signal.\n"), 1);
	i = -1;
	data = (t_minishell_data *)malloc(sizeof(t_minishell_data));
	if (!data)
		return (1);
	data->envs = NULL;
	while (envp[++i])
		ft_export(envp[i], &data->envs);
	lp_read_loop(&data);
	ft_free_envs(&data->envs);
	free(data);
	rl_clear_history();
	return (g_status);
}
