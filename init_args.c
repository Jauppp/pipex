/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:50:16 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/26 17:35:30 by cdomet-d         ###   ########lyon.fr   */
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
		if (var->apath)
			free(var->apath);
		var->apath = append_cmd(var->paths[i], var->args[0]);
		if (!var->apath)
			free_var(var, errno, "Append failed");
		if (access(var->apath, F_OK) == 0)
			return ;
		i++;
	}
	free_var(var, errno, NULL);
}

void	fetch_args(char **argv, t_var *var)
{
	char	*temp;

	if (var->args)
		free_dtab(var->args);
	temp = NULL;
	temp = ft_strdup(argv[var->i]);
	tokenize(temp);
	var->args = ft_split(temp, ' ');
	reinit(temp);
	reverse_tokenize(var->args);
	if (!var->args)
		free_var(var, errno, NULL);
	var->i++;
}
