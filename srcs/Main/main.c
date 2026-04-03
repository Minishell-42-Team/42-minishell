/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/03 12:12:28 by vnaoussi         ###   ########.fr       */
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
	}
	else if (sig == SIGQUIT)
		g_status = 0;
}

static void	lp_read_loop(t_minishell_data **data)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("minishell> ");
		else
			line = readline(NULL);
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
		free_tokens(&(*data)->tokens);
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
