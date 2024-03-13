/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_error_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:15:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/13 10:57:28 by cdomet-d         ###   ########lyon.fr   */
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

void	print_error(int error_code, char *error_message)
{
	if (error_code)
		ft_putendl_fd(strerror(error_code), STDERR_FILENO);
	if (error_message)
		ft_putendl_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
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
