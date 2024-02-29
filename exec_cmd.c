/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 13:45:27 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(t_var *var)
{
	fprintf(stderr, "In first_cmd, %d\n", var->i);
	display_fds(*var);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
		execve(var->aPath, var->args, var->paths);	
	waitpid(var->id, NULL, 0);
	fprintf(stderr, "End first_cmd\n----\n");
}
void	exec_cmd(t_var *var)
{
	fprintf(stderr, "In exec_cmd, %d\n", var->i);

	fprintf(stderr, "End exec_cmd\n----\n");
}

void	exec_last_cmd(t_var *var)
{
	// char buf[700] = {'0'};

	fprintf(stderr, "In last_cmd, %d\n----\n", var->i);
	display_fds(*var);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
		execve(var->aPath, var->args, var->paths);	
	waitpid(var->id, NULL, 0);
// exiting with everything closed
	fprintf(stderr, "End last_cmd\n----\n");
}
