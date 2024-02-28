/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/28 13:36:42 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(char *argv[], char *envp[], t_var *var)
{
	int	ffd_0;
	int ffd_1;

	if (pipe(var->fd) == -1)
		free_var(var, errno, NULL);
	var->id[0] = fork();
	if (var->id[0] == -1)
		free_var(var, errno, NULL);
	if (var->id[0] == 0)
	{
		ffd_0 = open(argv[1], O_RDONLY);
		if (ffd_0 == -1)
			free_var(var, errno, NULL);
		printf("Child process 1\n");
		dup2(var->fd[1], STDOUT_FILENO);
		dup2(ffd_0, STDIN_FILENO);
		close(ffd_0);
		close(var->fd[1]);
		execve(var->apath, var->args, envp);	
	}
	waitpid(var->id[0], NULL, 0);
	close(var->fd[1]);
	fetch_args(argv, var);
	fetch_apath(var);
	var->id[1] = fork();
	if (var->id[1] == -1)
		free_var(var, errno, NULL);
	if (var->id[1] == 0)
	{
		printf("Child process 2\n");
		ffd_1 = open(argv[var->argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (ffd_1 == -1)
			free_var(var, errno, NULL);
		if (dup2(ffd_1, STDOUT_FILENO) == -1)
			free_var(var, errno, NULL);
		if (dup2(var->fd[0], STDIN_FILENO) == -1)
			free_var(var, errno, NULL);
		close(ffd_1);
		close(var->fd[0]);
		execve(var->apath, var->args, envp);	
	}
	waitpid(var->id[1], NULL, 0);
	close(var->fd[0]);
	printf("Children processes have finished\n");
}
