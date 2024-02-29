/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 13:19:35 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(t_var *var)
{
	fprintf(stderr, "In first_cmd, %d\n", var->i);
// open pipe 1
	if (pipe(var->fd1) == -1)
		free_var(var, errno, NULL);
// putting STDIN on infile
	if (dup2(var->files[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
// putting STDOUT on W end of pipe
	if (dup2(var->fd1[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
// closing infile fd
	close(var->files[R]);
// closing W end of pipe
	close(var->fd1[W]);
	// var->fd1[W] = 5000;
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
		execve(var->aPath, var->args, var->paths);	
	waitpid(var->id, NULL, 0);
// Exiting with R end of pipe open
	fprintf(stderr, "End first_cmd\n----\n");
}
void	exec_cmd(t_var *var)
{
	char buf[700] = {'0'};
	fprintf(stderr, "In exec_cmd, %d\n", var->i);
	if (pipe(var->fd2) == -1)
		free_var(var, errno, NULL);
	close(var->fd2[R]);
	if (dup2(var->fd2[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
	if (dup2(var->fd1[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
	read(STDIN_FILENO, &buf, 700);
	write(STDERR_FILENO, &buf, 700);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
	{
		execve(var->aPath, var->args, var->paths);	
	}
	waitpid(var->id, NULL, 0);
	close(var->fd2[W]);
	close(var->fd1[R]);
	pipe(var->fd1);
	close(var->fd1[W]);
	fprintf(stderr, "End exec_cmd\n----\n");
}

void	exec_last_cmd(t_var *var)
{
	fprintf(stderr, "In last_cmd, %d\n----\n", var->i);
// putting STDIN on R end of open pipe
	if (dup2(var->fd1[R], STDIN_FILENO) == -1)
		free_var(var, errno, NULL);
// putting STDOUT on outfile
	if (dup2(var->files[W], STDOUT_FILENO) == -1)
		free_var(var, errno, NULL);
// closing pipe
	close(var->fd1[R]);
// closing outfile
	close(var->files[W]);
	var->id = fork();
	if (var->id == -1)
		free_var(var, errno, NULL);
	if (var->id == 0)
		execve(var->aPath, var->args, var->paths);	
	waitpid(var->id, NULL, 0);
// exiting with everything closed
	fprintf(stderr, "End last_cmd\n----\n");
}
