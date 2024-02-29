/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:47:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 18:18:02 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_var var;

	if (argc < 4)
		print_error(1200, NULL);
	if (access(argv[1], R_OK) == -1)
		print_error(errno, NULL);
	init_var(&var, argc);
	fetch_path(envp, &var);
	while (var.i < (argc - 1))
	{
		fetch_args(argv, &var);
		fetch_aPath(&var);
		if (pipe(var.fd1) == -1)
			free_var(&var, errno, NULL);
		if (var.i == 3)
		{
			var.files[R] = open(argv[1], O_RDONLY);
			if (var.files[R] == -1)	
				free_var(&var, errno, NULL);
			exec_first_cmd(&var);
		}	
		else if (var.i == (argc - 1))
		{
			var.files[W] = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
			if (var.files[W] == -1)
				free_var(&var, errno, NULL);
			exec_last_cmd(&var);
		}
		else
		{
			exec_cmd(&var);
			close(var.fd1[R]);
		}
	}
	free_var(&var, EXIT_SUCCESS, NULL);
}
