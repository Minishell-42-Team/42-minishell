/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:01:17 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/10 13:40:04 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char *getcwd(char *buf, size_t size)
// getcwd(cwd, PATH_MAX) PATH_MAX souvent limite a 4096
// getcwd(NULL, 0) alloue dynamiquement la memoire pour le chemin
#include "builtin.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror ("pwd");
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}
