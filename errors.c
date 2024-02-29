/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:15:28 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 12:49:02 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error_code, char *error_message)
{
	if (error_message)
		fprintf(stderr, "%s\n", error_message);
	else if (error_code == 1200)
		fprintf(stderr, "Incorrect formatting\nPlease enter 'file1' 'cmd1' 'cmd2' \
'file2'.\nYou can add as many commands as you want.\n");
	else if (error_code)
		fprintf(stderr, "Errno : %s\n", strerror(error_code));
	exit(EXIT_FAILURE);
}
