/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:06:54 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/19 22:55:42 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef struct e_env_var
{
	char				*key;
	char				*value;
	struct e_env_var	*next;
}	t_env_var;

void	*ft_export(char *args, t_env_var **env_vars, t_list **execredirs);
void	add_env_var(t_env_var **head, char *key, char *value);
void	print_env_vars(t_env_var *env_var);
void	ft_free_envs(t_env_var **env_vars);
void	ft_unset(t_env_var **env_vars, char *key);
void	ft_env(t_env_var *envs);

#endif
