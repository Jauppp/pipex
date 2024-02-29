/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 15:05:56 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(t_var *var)
{
	fprintf(stderr, "In first_cmd, %d\n", var->i);
	var->tmpIn = var->fd1[R];
	close(var->fd1[R]);
	if (dup2(var->files[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
	if (dup2(var->fd1[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
	close(var->fd1[W]);
	close(var->files[R]);
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
	if (dup2(var->tmpIn, var->fd1[R]) == -1)
		free_var(var, errno, NULL);
	if (dup2(var->fd1[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
	var->tmpIn = var->fd1[R];
		close(var->fd1[R]);
	if (dup2(var->fd1[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
	close(var->fd1[W]);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
		execve(var->aPath, var->args, var->paths);	
	fprintf(stderr, "End exec_cmd\n----\n");
}

void	exec_last_cmd(t_var *var)
{
	fprintf(stderr, "In last_cmd, %d\n", var->i);
	close(var->fd1[W]);
	if (dup2(var->tmpIn, var->fd1[R]) == -1)
		free_var(var, errno, NULL);
	if (dup2(var->fd1[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
	close(var->fd1[R]);
	if (dup2(var->files[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
		execve(var->aPath, var->args, var->paths);	
	waitpid(var->id, NULL, 0);
	fprintf(stderr, "End last_cmd\n----\n");
}

	// fprintf(stderr, "fd1[R] %d\n", fcntl(var->fd1[R], F_GETFL));