/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 16:31:53 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(t_var *var)
{
	char *buf[700] = {0};

	fprintf(stderr, "In first_cmd, %d\n", var->i);
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
	fprintf(stderr, "stdin %d\n", fcntl(STDIN_FILENO, F_GETFL));
	fprintf(stderr, "stdout %d\n", fcntl(STDOUT_FILENO, F_GETFL));
	read(STDIN_FILENO, &buf, 700);
	write(STDERR_FILENO, &buf, 700);
	waitpid(var->id, NULL, 0);
	fprintf(stderr, "End first_cmd\n----\n");
}
void	exec_cmd(t_var *var)
{
	char *buf[700] = {0};
	
	fprintf(stderr, "In exec_cmd, %d\n", var->i);
	fprintf(stderr, "tmpIn %d\n", fcntl(var->tmpIn, F_GETFL));
	if (dup2(var->fd1[R], var->tmpIn) == -1)
		free_var(var, errno, NULL);
	if (dup2(var->fd1[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
	close(var->fd1[R]);
	if (dup2(var->fd1[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
	close(var->fd1[W]);
	fprintf(stderr, "stdin %d\n", fcntl(STDIN_FILENO, F_GETFL));
	fprintf(stderr, "stdout %d\n", fcntl(STDOUT_FILENO, F_GETFL));
	read(STDIN_FILENO, &buf, 700);
	write(STDERR_FILENO, &buf, 700);
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
	if (dup2(var->fd1[R], var->tmpIn) == -1)
		free_var(var, errno, NULL);
	if (dup2(var->fd1[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
	close(var->fd1[R]);
	if (dup2(var->files[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
	close(var->files[W]);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
		execve(var->aPath, var->args, var->paths);	
	waitpid(var->id, NULL, 0);
	fprintf(stderr, "End last_cmd\n----\n");
}
