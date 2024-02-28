/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/28 20:19:36 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(char *argv[], char *envp[], t_var *var)
{
	int	ffd_0;
	(void)envp;
	if (pipe(var->fd1) == -1)
		free_var(var, errno, NULL);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
	{
		ffd_0 = open(argv[1], O_RDONLY);
		if (ffd_0 == -1)
			free_var(var, errno, NULL);
		dup2(ffd_0, STDIN_FILENO);
		close(ffd_0);
		dup2(var->fd1[1], STDOUT_FILENO);
		close(var->fd1[1]);
		execve(var->apath, var->args, var->paths);	
	}
	waitpid(var->id, NULL, 0);
	close(var->fd1[1]);
	var->fd1[1] = 0;
}
void	exec_cmd(char *envp[], t_var *var)
{
	if (var->fd1[0] != 0)
	{
		if (pipe(var->fd2) == -1)
			free_var(var, errno, NULL);
		// close(var->fd2[0]);
		// var->fd2[0] = 0;
		fprintf(stderr, "Opening fd2\n");
		display_fds(*var);
	}
	else
	{
		if (pipe(var->fd1) == -1) 
			free_var(var, errno, NULL);
		close(var->fd2[0]);
		var->fd2[0] = 0;
		fprintf(stderr, "Opening fd1\n");
		display_fds(*var);
	}
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
	{
		if (var->fd1[0] != 0)
		{
			if (dup2(var->fd1[0], STDIN_FILENO) == -1)
				free_var(var, errno, NULL);
			fprintf(stderr, "Reading in fd1[0] \n");
			display_fds(*var);
			if (dup2(var->fd2[1], STDOUT_FILENO) == -1)
				free_var(var, errno, NULL);
			fprintf(stderr, "Writing in fd2[1] \n");
			display_fds(*var);
			close(var->fd1[0]);
			close(var->fd2[1]);
		}
		else
		{
			if (dup2(var->fd2[0], STDIN_FILENO) == -1)
				free_var(var, errno, NULL);
			fprintf(stderr, "Reading in fd2[0] \n");
			if (dup2(var->fd1[1], STDOUT_FILENO) == -1)
				free_var(var, errno, NULL);
			fprintf(stderr, "Writing in fd1[1] \n");
			close(var->fd2[0]);
			close(var->fd1[1]);
		}
		execve(var->apath, var->args, envp);
	}
	waitpid(var->id, NULL, 0);
	if (var->fd1[0] != 0)
	{
		close(var->fd1[0]);
		close(var->fd2[1]);
		var->fd1[0] = 0;
		var->fd2[1] = 0;
	}
	else
	{
		close(var->fd2[0]);
		close(var->fd1[1]);
		var->fd2[0] = 0;
		var->fd1[1] = 0;
	}
}

void	exec_last_cmd(char *argv[], char *envp[], t_var *var)
{
	int ffd_1;
	
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
	{
		ffd_1 = open(argv[var->argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (ffd_1 == -1)
			free_var(var, errno, NULL);
		if (dup2(ffd_1, STDOUT_FILENO) == -1)
			free_var(var, errno, NULL);
		if (var->fd2[0] != 0)
		{
			if (dup2(var->fd2[0], STDIN_FILENO) == -1)
				free_var(var, 0, "eh");
			close(var->fd2[0]);
		}
		else
		{
			if (dup2(var->fd1[0], STDIN_FILENO) == -1)
				free_var(var, 0, "zut");
			close(var->fd1[0]);
		}
		close(ffd_1);
		execve(var->apath, var->args, envp);	
	}
	waitpid(var->id, NULL, 0);
	close(var->fd2[0]);
	close(var->fd1[1]);
	close(var->fd2[1]);
	close(var->fd1[0]);
}	
