/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:44:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/06 15:59:25 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# define SIG_ERROR_MSG "Error : fail to catch a signal.\n"

#include <string.h>
#include <ctype.h>
#include <errno.h>

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
	char		*value;
	struct s_token	*next;
} t_token;

typedef struct	s_data
{
	char	*line;
	int	pos;
} t_data;

int    quit_error(char *msg);

t_token_type	get_operator_type(t_data *data);
char	*read_word_between_quotes(t_data *data, char quote);
char	*read_normal_word(t_data *data);
char	*read_word(t_data *data);
t_token	*new_token(t_token_type type, char *value);
void	add_token(t_token **head, t_token *new);
t_token	*lexer(char *line);
void	free_tokens(t_token *tokens);
void	print_tokens(t_token *tokens);
char	*token_type_str(t_token_type type);

#endif
