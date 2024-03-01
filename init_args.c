/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:50:16 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/01 18:28:33 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fetch_path(char **envp, t_v *v)
{
	size_t	i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			if (!path)
				free_v(v, errno, NULL);
			v->paths = ft_split(path, ':');
			free(path);
			if (!v->paths)
				free_v(v, errno, NULL);
		}
		i++;
	}
}

int	fetch_a_path(char *argv[], t_v *v)
{
	size_t	i;

	i = 0;
	fetch_args(argv, v);
	if (access(v->args[0], F_OK) == 0)
		return (EXIT_SUCCESS);
	while (v->paths[i])
	{
		if (v->a_path)
			free(v->a_path);
		v->a_path = append_cmd(v->paths[i], v->args[0]);
		if (!v->a_path)
			free_v(v, 0, "Append failed");
		if (access(v->a_path, F_OK) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	ft_printf("pipex: %s: %s\n", strerror(errno), v->args[0]);
	return (EXIT_FAILURE);
}

void	fetch_args(char **argv, t_v *v)
{
	char	*temp;

	if (v->args)
		free_dtab(v->args);
	if (v->i == v->ac - 1)
		return ;
	temp = NULL;
	temp = ft_strdup(argv[v->i]);
	tokenize(temp);
	v->args = ft_split(temp, ' ');
	reinit(temp);
	reverse_tokenize(v->args);
	if (!v->args)
		free_v(v, errno, NULL);
	v->i++;
}

void	fetch_files(char **argv, t_v *v)
{
	v->file[R] = open(argv[1], O_RDONLY);
	if (v->file[R] == -1)
		free_v(v, errno, NULL);
	v->file[W] = open(argv[v->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (v->file[W] == -1)
		free_v(v, errno, NULL);
}
