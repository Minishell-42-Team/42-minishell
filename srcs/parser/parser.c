/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 04:51:52 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/10 15:58:10 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  t_command_ast init_command()
{
    (*command) = (t_command_ast *)malloc(sizeof(t_command_ast));
    if (!(*command))
        return (0);
    (*command)->next = NULL;
    (*command)->command = NULL;
    (*command)->args = NULL;
    (*command)->redirs = NULL;
    return (1);
}

static int ft_addredirs(t_redir_file **head, t_token_type type, char *file)
{
    t_redir_file *node;

    node = (t_redir_file *)malloc(sizeof(t_redir_file));
    if (!node)
        return (0);
    node->next = NULL;
    node->type = type;
    node->file = ft_strdup(file);
    if (!*head)
        *head = node;
    else
    {
        node->next = *head;
        *head = node;
    }
    return (1);
}

static  int extract_command_param(t_command_ast *commands, t_token *tokens,
        t_token **token_current)
{
    if (!tokens)
        return (0);
    if (tokens->type == PIPE)
    {
        *token_current = tokens->next;
        return (1);
    }
    if (tokens->type == WORD)
        if (extract_command_param(commands, tokens->next, token_current) != -1)
            return (ft_lstadd_back(&command->args,
                    ft_lstnew(ft_strdup(tokens->value))), 1);
    else if (is_type_redir(tokens))
        if (extract_command(commands, tokens->next->next, token_current) != -1)
            return (ft_addredirs(&command->redirs, tokens->type,
                        tokens->next->value));
    return (-1);
}

static t_command_ast    *get_commands(t_token *tokens)
{
    t_token         *token_current;
    t_command_ast   *cmds;
    t_command_ast   *current_cmd;
    t_token         *head;

    if (!tokens)
        return (1);
    cmds = init_command();
    if (!cmds)
        return (NULL);
    current_cmd = cmds;
    head = tokens;
    while (extract_command(current_cmd, head, &token_current) == 1)
    {
        current_cmd->next = init_command();
        if (!current_cmd->next)
            return (ft_free_command(*cmds), NULL);
        command_current = command_current->next;
        head = token_current->next;
    }
    if (!token_current)
        return (cmds);
    return (ft_free_command(*cmds), NULL);
}

t_command_ast   *parser(t_token *tokens)
{
    t_command_ast   *commands;

    if (!tokens)
        return (NULL);
    if (!get_commands(&commands, tokens))
        return (NULL);
    return (commands);
}
