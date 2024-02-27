/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:47:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/27 17:15:53 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_var	var;

	if (argc < 2)
		print_error(0, "Please enter at least two arguments");
	if (access(argv[1], R_OK) == -1)
		print_error(errno, NULL);
	init_var(&var, argc);
	fetch_path(envp, &var);
	while (var.i < (argc - 1))
	{
		fetch_args(argv, &var);
		fetch_apath(&var);
		exec_first_cmd(argv, envp, &var);
	}
	// display_t_var(var);
	free_var(&var, EXIT_SUCCESS, NULL);
}
