/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:50:16 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 12:00:54 by cdomet-d         ###   ########lyon.fr   */
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
			var->paths = ft_split(path, ':');
			free(path);
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
	while (var->paths[i])
	{
		if (var->a_path)
			free(var->a_path);
		var->a_path = append_cmd(var->paths[i], var->args[0]);
		if (!var->a_path)
			free_var(var, errno, "Append failed");
		if (access(var->a_path, F_OK) == 0)
			return ;
		i++;
	}
	free_var(var, errno, "Command not found");
}

void	fetch_args(char **argv, t_var *var)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	var->args = ft_calloc(ft_dstrlen(argv) + 1, sizeof (char *));
	if (!var->args)
		free_var(var, errno, "Allocation for var->args failed");
	while (argv[i])
	{
		var->args[j] = ft_strdup(argv[i]);
		if (!var->args)
			free_var(var, errno, "Copying the command failed");
		i++;
		j++;
	}
	display_tab(var->args);
}
