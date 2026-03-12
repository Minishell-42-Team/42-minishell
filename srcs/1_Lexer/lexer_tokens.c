/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:54:24 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/12 15:34:34 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Lexer :
// Initialise index i
// Skip espaces
// Identifie type
// Appelle une fonction spécialisée
// Ajoute token à la liste
// Verifie les erreurs (ENCORE A VERIFIER TOTALEMENT!!!)
// Encore quelques fuites de memoire a gerer

#include "minishell.h"
//*************************************************************//

t_token_type	get_operator_type(t_data *data)
{
	char	c;

	c = data->line[data->pos];
	if (c == '|')
	{
        	return (PIPE);
	}
	if (c == '>' && data->line[data->pos + 1] && data->line[data->pos + 1] == '>')
	{
		data->pos++;
		return (APPEND);
	}
	if (c == '<' && data->line[data->pos + 1] && data->line[data->pos + 1] == '<')
	{
		data->pos++;
		return (HEREDOC);
	}
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	return (WORD);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

//************************FONCTIONS SPECIALISEES**************************************//

char	*read_word_between_quotes(t_data *data, char quote)
{
	char	buffer[1024];
	char	*tmp;
	int		buf_pos;
	int		i;

	buf_pos = 0;
	data->pos++;
	while (data->line[data->pos] && data->line[data->pos] != quote && buf_pos < 1023)
	{
		if (quote == '"' && data->line[data->pos] == '$')
		{
			data->pos++;
			tmp = expand_variable(data->line, &data->pos);
			if (!tmp)
				return (NULL);
			i = 0;
			while (tmp[i] && buf_pos < 1023)
			{
				buffer[buf_pos] = tmp[i];
				buf_pos++;
				i++;
			}
			free(tmp);
		}
		else
		{
			buffer[buf_pos] = data->line[data->pos];
			data->pos++;
			buf_pos++;
		}
	}
	if (data->line[data->pos] == quote)
		data->pos++;
	else
		{
			printf("syntax error: unclosed quote %c\n", quote);
			return (NULL);
		}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

char	*read_normal_word(t_data *data)
{
	char	buffer[1024];
	int		buf_pos;
	char	*tmp;
	int		i;

	buf_pos = 0;
	while (data->line[data->pos]
		&& !ft_isspace(data->line[data->pos])
		&& !is_quote(data->line[data->pos])
		&& !is_operator(data->line[data->pos]))
	{
		if (data->line[data->pos] == '$')
		{
			data->pos++;
			tmp = expand_variable(data->line, &data->pos);
			if (!tmp)
				return (NULL);
			i = 0;
			while (tmp[i] && buf_pos < 1023)
			{
				buffer[buf_pos] = tmp[i];
				buf_pos++;
				i++;
			}
			free(tmp);
		}
		/*if (data->line[data->pos] == '\\')
		{
			data->pos++;
			continue ;
		}*/
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

char	*read_word(t_data *data)
{
	char	buffer[1024];
	char	*tmp;
	int		buf_pos;
	int		i;

	buf_pos = 0;
	tmp = NULL;
	while (data->line[data->pos]
		&& !ft_isspace(data->line[data->pos])
		&& !is_operator(data->line[data->pos]))
	{
		if (is_quote(data->line[data->pos]))
			tmp = read_word_between_quotes(data, data->line[data->pos]);
		else
			tmp = read_normal_word(data);
		if (!tmp)
			return (NULL);
		i = 0;
		while (tmp[i] && buf_pos < 1023)
		{
			buffer[buf_pos] = tmp[i];
			buf_pos++;
			i++;
		}
		free(tmp);
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

//**************************************************************//

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*node;

	node = NULL;
	if (!*head)
	{
		*head = new;
	}
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

/*void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}*/

//**************************************************************//

t_token	*lexer(char *line)
{
	t_data	data;
	t_token	*tokens;
	char	*word;
	t_token	*tok;
	t_token_type	type;

	data.line = line;
	tokens = NULL;
	data.pos = 0;

	while (data.line[data.pos])
	{
		while (ft_isspace(data.line[data.pos]))
			data.pos++;
		if (!data.line[data.pos])
			break ;
		type = get_operator_type(&data);
		if (type != WORD)
		{
			add_token(&tokens, new_token(type, NULL));
			data.pos++;
		}
		else
		{
			word = read_word(&data);
			tok = new_token(WORD, word);
			if (!tok)
			{
				free(word);
				free_tokens(tokens);
				return (NULL);
			}
			add_token(&tokens, tok);
			//free(word);
		}
	}
	return (tokens);
}


/*
int	main()
{
	char *line0 = "echo \"hello world\" | grep hello | wc -l >> file.txt";
	char *line0a = "echo \"hello world | grep hello | wc -l >> file.txt"; // quote non fermee
	char *line1 = "cat << EOF";
	char *line2 = "echo hello\"world\""; // melange texte + quotes doubles
	char *line3 = "\'hello world\'"; // quotes simples
	char *line3a = "\'hello world"; // quotes simples non fermees
	char *line4 = "ls -la"; // commande simple
	char *line5 = "ls | wc";
	char *line6 = "ls -l | grep .c"; // pipe avec arguments
	char *line7 = "";
	char *line8 = "echo hello>file"; // redirection sans espace
	char *line8b = "echo hello > file";
	char *line8c = "cat<<EOF"; // sans espaces
	char *line8d = "cat << EOF";
	char *line9 = "grep \"main\" <file.c | wc -l >> result.txt"; // commande complexe
	char *line9a = "echo \\ word"; // \ a ne pas traiter dans le sujet
	char *line9b = "echo ; word"; // ; a ne pas traiter aussi

	t_token *tokens = lexer(line3a);
	t_token *tmp = tokens;

	while (tmp)
	{
		printf("Token: %d", tmp->type);
        	if (tmp->value)
            		printf(" (%s)", tmp->value);
        	printf("\n");
        	tmp = tmp->next;
	}
	free_tokens(tokens);
	return (0);
}*/
/*
#include <stdio.h>
#include <stdlib.h>

void	print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
			printf("WORD     | %s\n", tmp->value);
		else if (tmp->type == PIPE)
			printf("PIPE     | |\n");
		else if (tmp->type == REDIR_IN)
			printf("REDIR_IN | <\n");
		else if (tmp->type == REDIR_OUT)
			printf("REDIR_OUT| >\n");
		else if (tmp->type == APPEND)
			printf("APPEND   | >>\n");
		else if (tmp->type == HEREDOC)
			printf("HEREDOC  | <<\n");
		tmp = tmp->next;
	}
}

void	test_lexer(const char *input)
{
	printf("\nCOMMAND: %s\n", input);
	t_token *tokens = lexer((char *)input);
	if (!tokens)
	{
		printf("Lexer returned NULL (probably unclosed quote)\n");
		return;
	}
	print_tokens(tokens);
	free_tokens(tokens);
}


int	main(void)
{
	// 1️⃣ Commandes simples
	test_lexer("echo hello");
	test_lexer("ls -l");

	// 2️⃣ Quotes simples
	test_lexer("echo \"hello world\"");
	test_lexer("echo 'hello world'");
	test_lexer("echo \"hello\"");
	test_lexer("echo ''");

	// 3️⃣ Mots mixtes
	test_lexer("echo hello\"world\"");
	test_lexer("echo \"hello\"world");
	test_lexer("echo \"hello\"\"world\"");
	test_lexer("echo 'hello'\"world\"");
	test_lexer("echo 'a'b\"c\"");

	// 4️⃣ Pipes
	test_lexer("ls | wc");
	test_lexer("echo a | grep a | wc -l");

	// 5️⃣ Redirections
	test_lexer("cat < file.txt");
	test_lexer("echo hello > out.txt");
	test_lexer("echo hello >> out.txt");
	test_lexer("cat << EOF");

	// 6️⃣ Combinaisons
	test_lexer("grep \"main\" < file.c | wc -l >> result.txt");
	test_lexer("echo \"hello\"world | cat > out.txt");

	// 7️⃣ Cas invalides / edge
	test_lexer("echo \"hello"); // unclosed quote
	test_lexer("echo      hello"); // espaces multiples
	test_lexer("echo>out.txt"); // redirection collée aux mots
	test_lexer("echo a\"b\"'c'd"); // mots mixtes + quotes multiples

	return 0;
}*/
