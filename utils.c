/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:04:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/16 15:53:26 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_var(t_var	*var)
{
	var->paths = NULL;
	var->args = NULL;
	var->a_path = NULL;
	var->files.infile = NULL;
	var->files.outfile = NULL;
}

void	display_tab(char **tab)
{
	unsigned int	i;

	ft_printf("\n----\n");
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

size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			count++;
		if (s[i] == DQUOTE || s[i] == SQUOTE)
		{
			while (s[i] && (s[i] != DQUOTE || s[i] != SQUOTE))
				i++;
		}
		if (s[i])
			i++;
	}
	if (s[i - 1] == c)
		count--;
	return (count + 1);
}
