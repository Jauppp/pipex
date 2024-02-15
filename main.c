/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:06:26 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 10:29:29 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_var	var;

	init_var(&var);
	(void)argc;
	fetch_path(envp, &var);
	display_tab(var.path);
	var.cmd_1 = fetch_cmd_1(argv, 1);
	if (!var.cmd_1)
		return (EXIT_FAILURE);
	find_absolute_path(&var);
	printf("absolute path : %s\n", var.a_path);
	var.file_1 = ft_strdup(argv[2]);
	printf("cmd : %s\n", var.cmd_1);
	execve(var.a_path, &var.cmd_1, var.path);
	free_var(&var, EXIT_SUCCESS, NULL);
}
