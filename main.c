/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:47:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/13 11:31:39 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_var	v;

	if (argc != 5)
		print_error(0, FORM_ERR);
	init_var(&v, argc);
	fetch_path(envp, &v);
	while (v.i < v.ac)
	{
		fetch_args(argv, &v);
		v.i++;
		fetch_a_path(&v);
		if (pipe(v.fd) == -1)
			free_v(&v, errno, NULL);
		fork_and_exec(&v, argv);
		if (dup2(v.fd[R], v.tmp_in) == -1)
			free_v(&v, errno, NULL);
		close(v.fd[W]);
		close(v.fd[R]);
	}
	close(v.tmp_in);
	v.tmp_in = 0;
	while (wait(0) != -1 && errno != ECHILD)
		;
	free_v(&v, EXIT_SUCCESS, NULL);
}
