/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:15:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/11 17:20:19 by cdomet-d         ###   ########lyon.fr   */
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
		ft_putendl_fd(FORM_ERR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
