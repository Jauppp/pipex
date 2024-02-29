/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:04:15 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:11 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_var(t_var	*var, int argc)
{
	var->aPath = NULL;
	var->argc = argc;
	var->args = NULL;
	var->fd1[0] = 0;
	var->fd1[1] = 0;
	var->files[0] = 0;
	var->files[1] = 0;
	var->fd2[0] = 0;
	var->fd2[1] = 0;
	var->tmpIn = 0;
	var->i = 2;
	var->id = 0;
	var->paths = NULL;
}

void	tokenize(char *str)
{
	size_t	i;
	bool	quote;
	char	c;

	i = 0;
	quote = false;
	while (str[i])
	{
		if (quote == false && (str[i] == DQUOTE || str[i] == SQUOTE))
		{
			quote = true;
			c = str[i];
			str[i] = ' ';
			i++;
		}
		if (quote == true && str[i] == ' ')
			str[i] = str[i] * -1;
		if (quote == true && str[i] == c)
		{
			str[i] = ' ';
			quote = false;	
		}
		i++;
	}
}

void	reverse_tokenize(char **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] < 0)
				tab[i][j] = tab[i][j] * -1;
			j++;
		}
		i++;
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
