/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:16:52 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/05 12:05:23 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,     // <
	OUTPUT,    // >
	APPEND,    // >>
	HEREDOC,   // <<
} t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char		*value;
	struct s_token	*next;
} t_token


typedef struct	s_data
{
	t_token		*token;
} t_data


#endif
