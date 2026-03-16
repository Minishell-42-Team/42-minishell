/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:19:42 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/16 14:58:04 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    if (argc != 2)
        return (0);
    if (ft_strcmp(argv[1], "export") == 0)
        ft_export(NULL, envp);
    else if (ft_strcmp(argv[1], "unset") == 0)
        return (0);
    return (0);
}
