/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/13 11:16:48 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_and_exec(t_var *v, char *argv[])
{
	v->id = fork();
	if (v->id == -1)
		free_v(v, errno, NULL);
	if (v->id == 0)
	{
		if (v->i == 3)
		{
			if (access(argv[1], R_OK) == -1)
				v->file[R] = open("/dev/null", O_RDONLY);
			else
				v->file[R] = open(argv[1], O_RDONLY);
			if (v->file[R] == -1)
				free_v(v, errno, NULL);
			exec_first_cmd(v);
		}
		else if (v->i == (v->ac))
		{
			v->file[W] = open(argv[v->ac], O_CREAT | O_TRUNC | O_RDWR, 0777);
			if (v->file[W] == -1)
				free_v(v, errno, NULL);
			exec_last_cmd(v);
		}
		else
			exec_cmd(v);
	}
}

void	exec_first_cmd(t_var *v)
{
	if (dup2(v->file[R], STDIN_FILENO) == -1)
		free_v(v, errno, "OUT");
	if (dup2(v->fd[W], STDOUT_FILENO) == -1)
		free_v(v, errno, "IN");
	close(v->fd[W]);
	close(v->fd[R]);
	close(v->file[R]);
	if (v->a_path && access(v->a_path, R_OK) != -1)
		execve(v->a_path, v->args, v->paths);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_v(v, 0, NULL);
	print_error(errno, NULL);
}

void	exec_cmd(t_var *v)
{
	if (dup2(v->tmp_in, STDIN_FILENO) == -1)
		free_v(v, errno, NULL);
	if (dup2(v->fd[W], STDOUT_FILENO) == -1)
		free_v(v, errno, NULL);
	close(v->fd[R]);
	close(v->fd[W]);
	if (v->a_path && access(v->a_path, R_OK) != -1)
		execve(v->a_path, v->args, v->paths);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_v(v, 0, NULL);
	print_error(errno, NULL);
}

void	exec_last_cmd(t_var *v)
{
	close(v->fd[W]);
	close(v->fd[R]);
	if (dup2(v->tmp_in, STDIN_FILENO) == -1)
		free_v(v, errno, NULL);
	if (dup2(v->file[W], STDOUT_FILENO) == -1)
		free_v(v, errno, NULL);
	close(v->file[W]);
	if (v->a_path && access(v->a_path, R_OK) != -1)
		execve(v->a_path, v->args, v->paths);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_v(v, 0, NULL);
	print_error(errno, NULL);
}