/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:06:26 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/16 13:32:51 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_var	var;
	t_proc	id;

	init_var(&var);
	(void)argc;
	fetch_path(envp, &var);
	fetch_args(argv, &var);
	display_tab(var.args);
	find_absolute_path(&var);
	printf("absolute path : %s\n\n", var.a_path);
	id.p1 = fork();
	if (id.p1 == 0)
	{
		if (execve(var.a_path, var.args, envp) == -1)
			free_var(&var, EXIT_FAILURE, strerror(errno));
		printf("This is the child process ! id = %d\n", id.p1);
	}
	if (id.p1 != 0)
		wait(NULL);
	printf("Parent process, id = %d\n", id.p1);
	free_var(&var, EXIT_SUCCESS, NULL);
}
