/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 04:51:52 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/11 19:53:44 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_ast *init_command()
{
    t_command_ast   *command;

    command = (t_command_ast *)malloc(sizeof(t_command_ast));
    if (!command)
        return (NULL);
    command->next = NULL;
    command->command = NULL;
    command->args = NULL;
    command->redirs = NULL;
    return (command);
}

static int ft_addredir(t_redir_file **head, t_token_type type, char *file)
{
    t_redir_file    *node;

    node = (t_redir_file *)malloc(sizeof(t_redir_file));
    if (!node)
        return (0);
    node->next = NULL;
    node->type = type;
    node->file = ft_strdup(file);
    if (!node->file)
        return (free(node), 0);
    if (!*head)
        *head = node;
    else
    {
        node->next = *head;
        *head = node;
    }
    return (1);
}

int get_command_param(t_command_ast *command, t_token *token,
        t_token **current_token)
{
    t_list  *node;

    node = NULL;
    if (!token)
        return (affect_token(current_token, NULL), 1);
    else if (token->type == PIPE)
        return (affect_token(current_token, token->next), 1);
    else if (token->type == WORD && !command->command)
    {
        command->command = ft_strdup(token->value);
        if (!command->command)
            return (0);
    }
    else if (is_type_redir(token) && token->next->type == WORD)
        return (ft_addredir(&command->redirs, token->type, token->next->value)
            && get_command_param(command, token->next->next, current_token));
    else
    {
        node = ft_lstnew(ft_strdup(token->value));
        if (!node)
            return (0);
        ft_lstadd_back(&command->args, node);
    }
    return (get_command_param(command, token->next, current_token));
}

static t_command_ast    *get_commands(t_token *tokens)
{
    t_token         *current_token;
    t_command_ast   *cmds;
    t_command_ast   *current_cmd;
    t_token         *head;

    if (!tokens)
        return (NULL);
    cmds = init_command();
    if (!cmds)
        return (NULL);
    current_cmd = cmds;
    head = tokens;
    current_token = tokens;
    while (get_command_param(current_cmd, head, &current_token)
        && current_token)
    {
        current_cmd->next = init_command();
        if (!current_cmd->next)
            return (ft_free_command(&cmds), NULL);
        current_cmd = current_cmd->next;
        head = current_token;
    }
    if (!current_token)
        return (cmds);
    return (ft_free_command(&cmds), NULL);
}

t_command_ast   *parser(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    return (get_commands(tokens));
}
