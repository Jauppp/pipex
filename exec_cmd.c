/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:03:59 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/27 17:39:58 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(char *argv[], char *envp[], t_var *var)
{
	int	ffd_0;
	int ffd_1;
	char buf[654];

	(void)envp;
	errno = 0;
	ffd_0 = open(argv[1], O_RDONLY);
	if (ffd_0 == -1)
		free_var(var, errno, NULL);
	ffd_1 = open(argv[var->argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (ffd_1 == -1)
		free_var(var, errno, NULL);
	pipe(var->fd);
	if (errno)
		free_var(var, 0, "fuck");
	display_t_var(*var);
	dup2(ffd_0, var->fd[0]);
	dup2(ffd_1, var->fd[1]);
	read(var->fd[0], &buf, 654);
	write(ffd_1, &buf, 654);
	close(ffd_0);
	close(ffd_1);
	close(var->fd[0]);
	close(var->fd[1]);
	// printf("this is the parent process\n");
}
