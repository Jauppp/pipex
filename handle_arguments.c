/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:50:16 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/16 13:33:37 by cdomet-d         ###   ########lyon.fr   */
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
	char	*temp;

	temp = NULL;
	i = 2;
	while (argv[i])
	{
		if (temp)
			free(temp);
		temp = ft_strdup(argv[i]);
		tokenize(temp);
		var->args = ft_split(temp, ' ');
		reverse_tokenize(var->args);
		if (!var->args)
			free_var(var, errno, "Allocation for var->arg failed");
		i++;
	}
	if (temp)
		free (temp);
}

void	fetch_files(char **argv, t_var *var)
{
	if (access(argv[1], R_OK) == -1)
		var->files.infile = "u/dev/null";
	else
		var->files.infile = ft_strdup(argv[1]);
	if (access(argv[ft_dstrlen(argv) - 1], W_OK) == -1)
		var->files.outfile = "u/dev/null";
	else
		var->files.outfile = ft_strdup(argv[ft_dstrlen(argv) - 1]);
}
