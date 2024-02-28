/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:47:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/28 18:36:31 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_var	var;

	if (argc < 4)
		print_error(1200, NULL);
	if (access(argv[1], R_OK) == -1)
		print_error(errno, NULL);
	init_var(&var, argc);
	fetch_path(envp, &var);
	while (var.i < (argc - 1))
	{
		fetch_args(argv, &var);
		fetch_apath(&var);
		if (var.i == 3)
			exec_first_cmd(argv, envp, &var);
		else if (var.i > 3 && (var.i < argc - 1))
			exec_cmd(envp, &var);
		else
			exec_last_cmd(argv, envp, &var);
	}
	free_var(&var, EXIT_SUCCESS, NULL);
}
