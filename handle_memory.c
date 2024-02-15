/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:29:41 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 11:13:41 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_var(t_var *var, int exit_code, char *error_message)
{
	if (var->paths)
		free_dtab(var->paths);
	if (var->args)
		free_dtab(var->args);
	if (var->a_path)
		free(var->a_path);
	if (var->cmd_1)
		free(var->cmd_1);
	if (var->cmd_2)
		free(var->cmd_2);
	if (var->file_1)
		free(var->file_1);
	if (var->file_2)
		free(var->file_2);
	init_var(var);
	if (exit_code || error_message)
		print_error(exit_code, error_message);
	else
		exit(EXIT_SUCCESS);
}

void	free_dtab(char **dtab)
{
	size_t	i;

	i = 0;
	if (!dtab)
		return ;
	while (dtab[i])
	{
		free(dtab[i]);
		i++;
	}
	free(dtab);
	dtab = NULL;
	return ;
}
