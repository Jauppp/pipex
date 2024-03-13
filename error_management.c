/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:15:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/13 11:14:53 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error_code, char *error_message)
{
	if (error_code && error_code != 1200)
		ft_putendl_fd(strerror(error_code), STDERR_FILENO);
	if (error_message)
		ft_putendl_fd(error_message, STDERR_FILENO);
	else if (error_code == 1200)
		ft_putendl_fd("Incorrect formatting\nPlease enter 'file1' 'cmd1' 'cmd2' \
'file2'.\nYou can add as many commands as you want.", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
