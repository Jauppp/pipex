/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:25:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 11:36:12 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* DELETE THIS BEFORE CORRECTION*/

void	display_tab(char **tab, char *str)
{
	unsigned int	i;

	printf("%s : ", str);
	i = 0;
	while (tab && tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
	printf("\n");
}

void	display_t_var(t_var var)
{
	// ft_printf("\n----\n");
	// display_tab(var.paths, "Paths");
	display_tab(var.args, "Arguments");
	// ft_printf("Absolute path : %s\n", var.apath);
	ft_printf("fd1[0] : %d || fd1[1] %d\n", var.fd1[0], var.fd1[1]);
	ft_printf("fd2[0] : %d || fd2[1] %d\n", var.fd2[0], var.fd2[1]);
	// ft_printf("id : %d\n", var.id);
	// ft_printf("argc : %d\n", var.argc);
	// ft_printf("i : %d\n", var.i);
	// ft_printf("----\n\n");
}

void	display_fds(t_var var)
{
	fprintf(stderr, "fd1[0], %d\n", var.fd1[0]);
	fprintf(stderr, "fd1[1], %d\n", var.fd1[1]);
	fprintf(stderr, "file[0], %d\n", var.files[0]);
	fprintf(stderr, "file[1], %d\n", var.files[1]);
	// fprintf(stderr, "fd2[0], %d\n", var.fd2[0]);
	// fprintf(stderr, "fd2[1], %d\n", var.fd2[1]);
	fprintf(stderr, "----\n");
}