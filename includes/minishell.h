/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:44:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/01 21:34:38 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# define SIG_ERROR_MSG "Error : fail to catch a signal.\n"
# include <string.h>
# include <ctype.h>

extern int	g_status;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir_file
{
	struct s_redir_file	*next;
	t_token_type		type;
	char				*file;
	int					heredoc_fd;
}	t_redir_file;

typedef struct s_command_ast
{
	struct s_command_ast	*next;
	char					*command;
	t_list					*args;
	t_redir_file			*redirs;
}	t_command_ast;

typedef struct s_data
{
	char		*line;
	int			pos;
	t_env_var	*env_vars;
}	t_data;

typedef struct s_minishell_data
{
	t_command_ast	*cmds;
	t_token			*tokens;
	t_env_var		*envs;
	t_list			*execdirs;
}	t_minishell_data;

int				quit_error(char *msg);
t_token_type	get_operator_type(t_data *data);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new);
t_token			*lexer(char *line, t_env_var *env_vars);
void			free_tokens(t_token *tokens);
void			print_tokens(t_token *tokens);
char			*token_type_str(t_token_type type);
t_command_ast	*parser(t_token *tokens);
void			print_commands(t_command_ast *cmds);
int				is_type_redir(t_token *token);
void			affect_token(t_token **token, t_token *token_to_be);
void			ft_free_command(t_command_ast **command);
char			*expand_variable(const char *str,
					int *pos, t_env_var *env_vars);
void			ft_free(void **nptr);
int				affect_command_param(t_command_ast *command, t_token *token);
void			ft_exit(t_minishell_data **data);
void			run_command(t_command_ast *command, t_minishell_data **data);
int				apply_redirections(t_redir_file *redir);
int				handle_heredoc(const char *delimiter);
//void			process_heredoc(t_command_ast *cmds);
void			ft_free_table(char ***table, int len);
void			fork_child_do(t_command_ast *command, t_minishell_data **data);
void			fork_parent_do(int *fd_in, t_command_ast *command,
					int pipefd_in, int pipefd_out);
void			execute_pipeline(t_command_ast *cmds, t_minishell_data **data);
int				is_operator(char c);
int				is_quote(char c);
int				ft_isspace(char c);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new);
int				check_built_parent(t_command_ast *cmd, t_minishell_data **data);
int				get_fdin(t_command_ast *cmd);
int				get_fdout(t_command_ast *cmd);
int				open_file(t_redir_file *redir);
int				exec_builtin(t_command_ast *cmd, t_minishell_data **data);
//int				ft_check_parent_builtin(t_command_ast *cmd);
#endif
