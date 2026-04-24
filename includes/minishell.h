/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:44:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/24 12:28:17 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# define SIG_ERROR_MSG "Error : fail to catch a signal.\n"
# define TOKEN_MSG "Minishell: syntax error near unexpected token `newline'\n"
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
	SEMICOLON,
	AND_IF,
	AND,
	OR_IF,
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
	int					quoted;
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

typedef struct s_match_data
{
	t_list	**args;
	int		*count;
	char	*path;
	char	*pattern;
}	t_match_data;

int				quit_error(char *msg);
t_token_type	get_operator_type(t_data *data);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new);
t_token			*lexer(char *line, t_env_var *env_vars);
void			expander_tokens(t_token *tokens, t_env_var *envs);
char			*get_env_val(const char *key, t_env_var *env_vars);
char			*ft_join_free(char *s1, char *s2);
char			*remove_quotes(char *str);
void			clean_quotes_command(t_command_ast *cmd);
void			free_tokens(t_token **tokens);
void			print_tokens(t_token *tokens);
char			*token_type_str(t_token_type type);
t_command_ast	*parser(t_token *tokens);
void			print_commands(t_command_ast *cmds);
int				is_type_redir(t_token *token);
void			affect_token(t_token **token, t_token *token_to_be);
void			ft_free_command(t_command_ast **command);
int				ft_addredir(t_redir_file **head, t_token_type type, char *f);
char			*handle_relative_command(char *command);
char			**fill_args(t_command_ast *cmd, char *access_link, int len);
void			restore_io(int *stdin_save, int *stdout_save);
char			*expand_variable(const char *s, int *p, t_env_var *ev);
void			ft_free(void **nptr);
int				affect_command_param(t_command_ast *cmd, t_token *t);
int				ft_exit(t_command_ast *cmd, t_minishell_data **data, int pid);
void			ft_clean_all(t_minishell_data **data);
int				apply_redirections(t_redir_file *redir);
int				handle_heredoc(const char *delim, int quoted,
					t_minishell_data **data);
void			ft_wait_child(t_command_ast *cmd, pid_t *pids);
int				prepare_heredoc(t_command_ast *cmds, t_minishell_data **data);
void			ft_free_table(char ***table, int len);
void			fork_child_do(t_command_ast *command, t_minishell_data **data,
					int pid);
void			fork_parent_do(int *fd_in, t_command_ast *cmd,
					int p_i, int p_o);
void			execute_pipeline(t_command_ast *cmds, t_minishell_data **data);
int				is_operator(char c);
int				is_quote(char c);
int				ft_isspace(char c);
void			ignore_signals(void);
int				check_built_parent(t_command_ast *c, t_minishell_data **d, int pid);
void			handle_child(t_minishell_data **d, t_command_ast *c, int *p,
					int f);
int				check_built_parent(t_command_ast *c, t_minishell_data **d,
					int pid);
int				open_file(t_redir_file *redir);
int				exec_builtin(t_command_ast *cmd, t_minishell_data **data,
					int pid);
int				exec_simple_builtin_2(t_command_ast *cmd);
int				get_matched_args(t_command_ast *cmd);
void			handle_fork_signal(int sig);
void			handle_signal(int sig);
int				add_new_arg(t_list **args, char *content, int *count);
int				is_dir(const char *path);
int				is_p_dir(char *path);
void			get_pathname(char *path, const char *entry);
int				has_quotes(char *str);
int				ft_addredir(t_redir_file **head, t_token_type type, char *file);

#endif
