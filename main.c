/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:06:26 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 12:14:45 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_var	var;
	t_proc	ids;

	init_var(&var);
	(void)argc;
	fetch_path(envp, &var);
	fetch_args(argv, &var);
	find_absolute_path(&var);
	printf("absolute path : %s\n", var.a_path);
	ids.p1 = fork();
	if (ids.p1 == 0)
	{
		execve(var.a_path, var.args, envp);
		printf("This is the child process ! id = %d\n", ids.p1);
	}
	if (ids.p1 != 0)
		wait(NULL);
	printf("This should only be printed by the parent process, \
		id = %d\n", ids.p1);
	free_var(&var, EXIT_SUCCESS, NULL);
}
