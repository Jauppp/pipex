/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:15:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 10:38:48 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error_code, char *error_message)
{
	printf("%d\n", error_code);
	if (error_message)
		ft_printf("%s\n", error_message);
	if (error_code)
		ft_printf("Errno : %s\n", strerror(error_code));
	exit(EXIT_FAILURE);
}
