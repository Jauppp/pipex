/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:29:41 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/07 14:41:44 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_v(t_var *v, int exit_code, char *error_message)
{
	if (v->paths)
		free_dtab(v->paths);
	if (v->args)
		free_dtab(v->args);
	if (v->a_path)
		free(v->a_path);
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

void	reinit(char *temp)
{
	free(temp);
	temp = NULL;
}
