/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:48:55 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/01 18:28:33 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exec_first_cmd(t_v *v)
{
	fprintf(stderr, "In first_cmd, %d\n", v->i);
	v->tmp_in = v->fd[R];
	// close(v->fd[R]);
	if (dup2(v->file[R], STDIN_FILENO) == -1)
		free_v(v, errno, NULL);
	if (dup2(v->fd[W], STDOUT_FILENO) == -1)
		free_v(v, errno, NULL);
	close(v->fd[W]);
	close(v->file[R]);
	display_fds(*v);
	v->id = fork();
	if (v->id == -1)
		free_v(v, errno, NULL);
	if (v->id == 0)
		execve(v->a_path, v->args, v->paths);
	waitpid(v->id, NULL, 0);
	fprintf(stderr, "End first_cmd\n----\n");
}
void exec_cmd(t_v *v)
{
	fprintf(stderr, "In exec_cmd, %d\n", v->i);

	if (dup2(v->tmp_in, STDIN_FILENO) == -1)
		free_v(v, errno, NULL);
	// if (dup2(v->fd[R], STDIN_FILENO) == -1)
	//     free_v(v, errno, NULL);
	v->tmp_in = v->fd[R];
	// close(v->fd[R]);
	if (dup2(v->fd[W], STDOUT_FILENO) == -1)
		free_v(v, errno, NULL);
	close(v->fd[W]);
	display_fds(*v);
	v->id = fork();
	if (v->id == -1)
		free_v(v, errno, NULL);
	if (v->id == 0)
		execve(v->a_path, v->args, v->paths);
	fprintf(stderr, "End exec_cmd\n----\n");
}

void exec_last_cmd(t_v *v)
{
	fprintf(stderr, "In last_cmd, %d\n", v->i);

	close(v->fd[W]);
	if (dup2(v->tmp_in, v->fd[R]) == -1)
		free_v(v, errno, NULL);
	if (dup2(v->fd[R], STDIN_FILENO) == -1)
		free_v(v, errno, NULL);
	close(v->fd[R]);
	if (dup2(v->file[W], STDOUT_FILENO) == -1)
		free_v(v, errno, NULL);
	display_fds(*v);
	v->id = fork();
	if (v->id == -1)
		free_v(v, errno, NULL);
	if (v->id == 0)
		execve(v->a_path, v->args, v->paths);
	// waitpid(v->id, NULL, 0);
	fprintf(stderr, "End last_cmd\n----\n");
}

// fprintf(stderr, "fd[R] %d\n", fcntl(v->fd[R], F_GETFL));