/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:25:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/26 10:48:11 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* DELETE THIS BEFORE CORRECTION*/

void	display_tab(char **tab, char *str)
{
	unsigned int	i;

	ft_printf("\n----\n");
	printf("%s\n", str);
	i = 0;
	while (tab[i])
	{
		if (i < 10)
			ft_printf("tab[%u]  : |%s|\n", i, tab[i]);
		else
			ft_printf("tab[%u] : |%s|\n", i, tab[i]);
		i++;
	}
	ft_printf("----\n\n");
}