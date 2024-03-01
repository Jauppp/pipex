/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:47:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/01 18:33:35 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_v	v;

	if (!envp || !*envp)
		print_error(0, "No environment");
	if (argc < 4)
		print_error(1200, NULL);
	init_v(&v, argc);
	fetch_path(envp, &v);
	while (v.i < (argc - 1))
	{
		fetch_a_path(argv, &v);
		if (pipe(v.fd) == -1)
			free_v(&v, errno, NULL);
		fork_and_exec(&v, argv);
		dup2(v.fd[R], v.tmp_in);
		close(v.fd[W]);
		close(v.fd[R]);
	}
	close(v.tmp_in);
	v.tmp_in = 0;
	while (wait(0) != -1 && errno != ECHILD);
	free_v(&v, EXIT_SUCCESS, NULL);
}
