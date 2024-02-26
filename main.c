/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:47:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/26 17:27:19 by cdomet-d         ###   ########lyon.fr   */
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
	init_var(&var);
	var.fd[0] = open(argv[1], O_RDONLY);
	// var.fd[1] = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fetch_path(envp, &var);
	while (var.i < (argc - 1))
	{
		fetch_args(argv, &var);
		find_absolute_path(&var);
		printf("%s\n", var.apath);
		display_tab(var.args, "Arguments");
	}
	free_var(&var, EXIT_SUCCESS, NULL);
}
