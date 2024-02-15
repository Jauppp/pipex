/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:04:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 11:08:24 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_var(t_var	*var)
{
	var->paths = NULL;
	var->args = NULL;
	var->a_path = NULL;
	var->cmd_1 = NULL;
	var->cmd_2 = NULL;
	var->file_1 = NULL;
	var->file_2 = NULL;
}

void	display_tab(char **tab)
{
	unsigned int	i;

	i = -1;
	while (tab[++i])
	{
		if (i < 10)
			ft_printf("tab[%u]  : |%s|\n", i, tab[i]);
		else
			ft_printf("tab[%u] : |%s|\n", i, tab[i]);
	}
}



char	*append_cmd(char const *s1, char const *s2)
{
	size_t		strjoin_len;
	size_t		i;
	size_t		j;
	char		*strjoin;

	if (!s1 || !s2)
		return (NULL);
	strjoin_len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = ft_calloc(strjoin_len + 2, sizeof (char));
	if (!strjoin)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		strjoin[i++] = s1[j++];
	strjoin[i] = '/';
	i++;
	j = 0;
	while (s2[j])
		strjoin[i++] = s2[j++];
	return (strjoin);
}
