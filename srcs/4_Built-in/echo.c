/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:37:39 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/19 12:38:47 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_n_options(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_list *args)
{
	int	flag_newline;

	flag_newline = 1;
	while (args && is_n_options((char *)args->content))
	{
		flag_newline = 0;
		args = args->next;
	}
	while (args)
	{
		printf("%s", (char *)args->content);
		if (args->next)
			printf(" ");
		args = args->next;
	}
	if (flag_newline)
		printf("\n");
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *test1[] = {"echo", "hello", NULL};
    char *test2[] = {"echo", "-n", "hello", NULL};
    char *test3[] = {"echo", "-nn", "hello", "world", NULL};
    char *test4[] = {"echo", "-nhello", NULL};
    char *test5[] = {"echo", "-n", "-n", "hello", NULL};
    char *test6[] = {"echo", NULL};
    char *test7[] = {"echo", "-n", NULL};

    printf("Test 1: echo hello\nExpected: hello\\n\nOutput:   ");
    ft_echo(test1);
    printf("\n\n");

    printf("Test 2: echo -n hello\nExpected: hello\nOutput:   ");
    ft_echo(test2);
    printf("\n\n");

    printf("Test 3: echo -nn hello world\nExpected: hello world\nOutput:   ");
    ft_echo(test3);
    printf("\n\n");

    printf("Test 4: echo -nhello\nExpected: -nhello\\n\nOutput:   ");
    ft_echo(test4);
    printf("\n\n");

    printf("Test 5: echo -n -n hello\nExpected: hello\nOutput:   ");
    ft_echo(test5);
    printf("\n\n");
	
	printf("Test 6: echo\nExpected: \\n\nOutput:   ");
    ft_echo(test6);
    printf("\n\n");

    printf("Test 7: echo -n\nExpected: (nothing)\nOutput:   ");
    ft_echo(test7);
    printf("\n\n");

    return 0;

}*/
