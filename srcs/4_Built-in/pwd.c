/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:01:17 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/20 13:09:12 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char *getcwd(char *buf, size_t size)
// getcwd(cwd, PATH_MAX) PATH_MAX souvent limite a 4096
// getcwd(NULL, 0) alloue dynamiquement la memoire pour le chemin
#include "builtin.h"

int	ft_pwd(void)
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
	return (0);
}
