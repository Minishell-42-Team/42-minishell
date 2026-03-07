/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:33:28 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/06 15:59:41 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *token_type_str(t_token_type type)
{
    if (type == WORD)
        return "WORD";
    if (type == PIPE)
        return "PIPE";
    if (type == REDIR_IN)
        return "REDIR_IN";
    if (type == REDIR_OUT)
        return "REDIR_OUT";
    if (type == APPEND)
        return "APPEND";
    if (type == HEREDOC)
        return "HEREDOC";
    return "TOKEN_NONE";
}

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TYPE: %s", token_type_str(tokens->type));
		if (tokens->value)
			printf(" | VALUE: %s", tokens->value);
       		else if (tokens->type == PIPE)
            		printf(" | VALUE: |");
        	else if (tokens->type == REDIR_OUT)
            		printf(" | VALUE: >");
        	else if (tokens->type == REDIR_IN)
            		printf(" | VALUE: <");
        	else if (tokens->type == APPEND)
            		printf(" | VALUE: >>");
        	else if (tokens->type == HEREDOC)
            		printf(" | VALUE: <<");
		printf("\n");
		tokens = tokens->next;
	}
}
