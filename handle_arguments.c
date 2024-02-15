/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:50:16 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/14 18:02:14 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fetch_path(char **envp, t_var *var)
{
	size_t	i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			if (errno)
				print_error(errno, NULL);
			var->path = ft_split(path, ':');
			if (errno)
				free_var(var, errno, NULL);
		}
		i++;
	}
}

void	find_absolute_path(t_var *var)
{
	size_t	i;

	i = 0;
	while (var->path[i])
	{
		if (var->a_path)
			free(var->a_path);
		var->a_path = append_cmd(var->path[i], var->cmd_1);
		if (!var->a_path)
			free_var(var, errno, "append failed");
		if (access(var->a_path, F_OK) == 0)
			return ;
		i++;
	}
	free_var(var, errno, "Command not found");
}



char	*fetch_cmd_1(char **argv, int arg)
{
	char	*cmd;

	cmd = ft_strdup(argv[arg]);
	if (errno)
		print_error(errno, NULL);
	if (cmd)
		return (cmd);
	return (NULL);
}
