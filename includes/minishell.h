/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:44:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/19 16:02:24 by clwenhaj         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# define SIG_ERROR_MSG "Error : fail to catch a signal.\n"

#include <string.h>
#include <ctype.h>

extern int g_status;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
} t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;

typedef struct s_redir_file
{
	struct s_redir_file *next;
	t_token_type		type;
	char				*file;
}	t_redir_file;

typedef	struct s_command_ast
{
	struct s_command_ast	*next;
	char					*command;
	t_list					*args;
	t_redir_file			*redirs;
}	t_command_ast;

typedef struct	s_data
{
	char	*line;
	int	pos;
} t_data;

typedef struct s_minishell_data
{
	t_command_ast	*cmds;
	t_token			*tokens;
	t_env_var		*envs;
}	t_minishell_data;

int				quit_error(char *msg);
t_token_type	get_operator_type(t_data *data);
char			*read_word_between_quotes(t_data *data, char quote);
char			*read_normal_word(t_data *data);
char			*read_word(t_data *data);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new);
t_token			*lexer(char *line);
void			free_tokens(t_token *tokens);
void			print_tokens(t_token *tokens);
char			*token_type_str(t_token_type type);
t_command_ast	*parser(t_token *tokens);
void			print_commands(t_command_ast *cmds);
int				is_type_redir(t_token *token);
void			affect_token(t_token **token, t_token *token_to_be);
void			ft_free_command(t_command_ast **command);
char    *expand_variable(const char *str, int *pos);
void			ft_free(void **nptr);
int				affect_command_param(t_command_ast *command, t_token *token);
void			ft_exit(t_minishell_data **data);

int		apply_redirections(t_redir_file *redirs);
int     handle_heredoc(const char *delimiter);


#endif
