/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:25:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/28 11:51:47 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* DELETE THIS BEFORE CORRECTION*/

void	display_tab(char **tab, char *str)
{
	unsigned int	i;

	// ft_printf("\n----\n");
	printf("| %s |\n", str);
	// ft_printf("\n----\n");
	i = 0;
	while (tab && tab[i])
	{
		if (i < 10)
			printf("tab[%u]  : |%s|\n", i, tab[i]);
		else
			printf("tab[%u] : |%s|\n", i, tab[i]);
		i++;
	}
	ft_printf("\n----\n\n");
}

void	display_t_var(t_var var)
{
	ft_printf("\n----\n");
	display_tab(var.paths, "Paths");
	display_tab(var.args, "Arguments");
	ft_printf("Absolute path : %s\n", var.apath);
	ft_printf("fd : %d || %d\n", var.fd[0], var.fd[1]);
	// ft_printf("id : %d\n", var.id);
	ft_printf("argc : %d\n", var.argc);
	ft_printf("i : %d\n", var.i);
	ft_printf("----\n\n");
}