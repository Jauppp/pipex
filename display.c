/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:25:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/01 18:28:33 by cdomet-d         ###   ########lyon.fr   */
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

void	display_t_v(t_v v)
{
	// ft_printf("\n----\n");
	// display_tab(v.paths, "Paths");
	display_tab(v.args, "Arguments");
	// ft_printf("Absolute path : %s\n", v.a_path);
	ft_printf("fd[0] : %d || fd[1] %d\n", v.fd[0], v.fd[1]);
	// ft_printf("id : %d\n", v.id);
	// ft_printf("argc : %d\n", v.argc);
	// ft_printf("i : %d\n", v.i);
	// ft_printf("----\n\n");
}

void	display_fds(t_v v)
{
	fprintf(stderr, "fd[0], %d\n", v.fd[0]);
	fprintf(stderr, "fd[1], %d\n", v.fd[1]);
	fprintf(stderr, "file[0], %d\n", v.file[0]);
	fprintf(stderr, "file[1], %d\n", v.file[1]);
	fprintf(stderr, "tmp.In %d\n", v.tmp_in);
	fprintf(stderr, "----\n");
}